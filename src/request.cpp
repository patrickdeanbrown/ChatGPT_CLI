//  request.cpp
//
// Handles curl request to ChatGPT API and response extraction

#include "request.hpp"
#include "chathistory.hpp"
#include <cstdlib>
#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream> // Required for parsing SSE

// StreamCallbackData struct is defined in request.hpp

std::string makeRequest(const std::string &message, ChatHistory &chatHistory, ftxui::ScreenInteractive* screen_ptr)
{
    // Add new user message to chat history
    chatHistory.addDialog("user", message);

    // Build JSON payload
    nlohmann::json payload;
    payload["model"] = "gpt-4o"; 
    payload["stream"] = true; // Enable streaming
    payload["messages"] = nlohmann::json::array(); // Ensure messages is an array

    for (const auto &[role, content] : chatHistory)
    {
        payload["messages"].push_back({{"role", role}, {"content", content}});
    }

    std::string payloadStr = payload.dump();

    CURL *curl = curl_easy_init();
    CURLcode res;

    if (curl)
    {
        StreamCallbackData callbackData;
        callbackData.chatHistory = &chatHistory;
        callbackData.screen = screen_ptr;
        callbackData.assistantMessageAdded = false;
        callbackData.currentAssistantResponse = ""; 

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payloadStr.c_str());

        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Accept: text/event-stream");

        const char *api_key = std::getenv("OPENAI_KEY");
        if (api_key == nullptr || std::string(api_key).empty())
        {
            std::cerr << "[ERROR] OPENAI_KEY environment variable not set." << std::endl;
            if (curl) curl_easy_cleanup(curl);
            if (headers) curl_slist_free_all(headers);
            return "{\"error\": {\"message\": \"OPENAI_KEY environment variable not set.\"}}";
        }
        std::string auth_header = "Authorization: Bearer " + std::string(api_key);
        headers = curl_slist_append(headers, auth_header.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &callbackData);
        
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            std::string curl_error_message = curl_easy_strerror(res);
            std::cerr << "curl_easy_perform() failed: " << curl_error_message << std::endl;
            if (!callbackData.assistantMessageAdded) {
                 chatHistory.addDialog("system", "API request failed: " + curl_error_message);
                 if(screen_ptr) screen_ptr->PostEvent(ftxui::Event::Custom); 
            }
             if (curl) curl_easy_cleanup(curl); 
             if (headers) curl_slist_free_all(headers);
            return ""; 
        }

        if (curl) curl_easy_cleanup(curl);
        if (headers) curl_slist_free_all(headers);
    }
    return ""; 
}

std::string getChatGPTResponseContent(const std::string &jsonStr)
{
    if (jsonStr.empty()) {
        return ""; 
    }

    try {
        nlohmann::json jsonResponse = nlohmann::json::parse(jsonStr);
        if (jsonResponse.contains("error")) {
            std::string errMsg = jsonResponse["error"].value("message", "Unknown error");
            return "[API Error] " + errMsg;
        }
        if (jsonResponse.contains("choices") && jsonResponse["choices"].is_array() && !jsonResponse["choices"].empty()) {
            if (jsonResponse["choices"][0].contains("message") && jsonResponse["choices"][0]["message"].contains("content")) {
                 return jsonResponse["choices"][0]["message"]["content"].get<std::string>();
            }
        }
        std::cerr << "[WARNING] getChatGPTResponseContent received unexpected JSON structure: " << jsonStr << std::endl;
        return ""; 
    } catch (const nlohmann::json::parse_error &e) {
        std::cerr << "[ERROR] Failed to parse supposed API JSON response: " << e.what() << "\nFull text: " << jsonStr << std::endl;
        return "[Error] Malformed response from server.";
    }
}

size_t _writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    StreamCallbackData* data = static_cast<StreamCallbackData*>(userp);

    std::string_view chunk_view(static_cast<char*>(contents), realsize);
    std::string chunk_str(chunk_view);
    std::istringstream chunk_stream(chunk_str);
    std::string line;

    while (std::getline(chunk_stream, line)) {
        if (line.empty() || line[0] == ':') { 
            continue;
        }

        if (line.rfind("data: ", 0) == 0) {
            std::string jsonData = line.substr(6);
            
            if (jsonData == "[DONE]") {
                if (data->screen) {
                    data->screen->PostEvent(ftxui::Event::Custom); 
                }
                return realsize; 
            }

            try {
                nlohmann::json j = nlohmann::json::parse(jsonData);
                std::string delta_content;

                if (j.contains("choices") && j["choices"].is_array() && !j["choices"].empty()) {
                    const auto& choice = j["choices"][0];
                    if (choice.contains("delta") && choice["delta"].is_object()) {
                        const auto& delta = choice["delta"];
                        if (delta.contains("content") && delta["content"].is_string()) {
                            delta_content = delta["content"].get<std::string>();
                        }
                    }
                } else if (j.contains("error")) { 
                    delta_content = "[API Error] " + j["error"].value("message", "Unknown error from stream");
                }

                if (!delta_content.empty()) {
                    data->currentAssistantResponse = delta_content; 

                    if (!data->assistantMessageAdded) {
                        if (!data->chatHistory->isEmpty()) {
                            try {
                                auto lastDialog = data->chatHistory->getLastDialog();
                                if (lastDialog.first == "system" && lastDialog.second == "Assistant is thinking...") {
                                    data->chatHistory->removeLastDialog();
                                }
                            } catch (const std::out_of_range& e) {
                                std::cerr << "Error checking last dialog: " << e.what() << std::endl;
                            }
                        }
                        data->chatHistory->addDialog("assistant", delta_content);
                        data->assistantMessageAdded = true;
                    } else {
                        data->chatHistory->appendToLastDialog(delta_content);
                    }
                    
                    if (data->screen) {
                        data->screen->PostEvent(ftxui::Event::Custom);
                    }
                }
            } catch (const nlohmann::json::parse_error& e) {
                std::cerr << "JSON parse error in stream: " << e.what() << ". Data: '" << jsonData << "'" << std::endl;
            }
        }
    }
    return realsize; 
}
