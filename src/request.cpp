//  request.cpp
//
// Handles curl request to ChatGPT API and response extraction

#include "request.hpp"
#include "chathistory.hpp"
#include <cstdlib>
#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>

std::string makeRequest(const std::string &message, ChatHistory &chatHistory)
{
    // Add new user message to chat history
    chatHistory.addDialog("user", message);

    // Build JSON payload
    nlohmann::json payload;
    payload["model"] = "gpt-4o"; // Updated to latest supported model

    // Add chat history
    for (const auto &[role, content] : chatHistory)
    {
        payload["messages"].push_back({{"role", role}, {"content", content}});
    }

    // Convert the JSON object to a string
    std::string payloadStr = payload.dump();

    // Set up CURL
    CURL *curl = curl_easy_init();
    CURLcode res;
    std::string response;

    if (curl)
    {
        // Set the URL for the request
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");

        // Set the request method to POST
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // Add in the payload
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payloadStr.c_str());

        // Add necessary headers
        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // Get API KEY from environment and check for presence
        const char *api_key = std::getenv("OPENAI_KEY");
        if (api_key == nullptr || std::string(api_key).empty())
        {
            std::cerr << "[ERROR] OPENAI_KEY environment variable not set. Please set it before running the CLI." << std::endl;
            curl_easy_cleanup(curl);
            curl_slist_free_all(headers);
            return "";
        }
        std::string auth_header = "Authorization: Bearer " + std::string(api_key);
        headers = curl_slist_append(headers, auth_header.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Function to receive the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _writeCallback);

        // Response data
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK)
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    return response;
}

std::string getChatGPTResponseContent(const std::string &jsonStr)
{
    // Parse the response and extract the assistant's message content
    try {
        nlohmann::json jsonResponse = nlohmann::json::parse(jsonStr);
        // If there is an error field, print it for the user
        if (jsonResponse.contains("error")) {
            std::string errMsg = jsonResponse["error"].contains("message") ? jsonResponse["error"]["message"].get<std::string>() : "Unknown error";
            std::cerr << "[OPENAI API ERROR] " << errMsg << std::endl;
            // Optionally print more details if available
            if (jsonResponse["error"].contains("type")) {
                std::cerr << "  Type: " << jsonResponse["error"]["type"] << std::endl;
            }
            if (jsonResponse["error"].contains("code")) {
                std::cerr << "  Code: " << jsonResponse["error"]["code"] << std::endl;
            }
            return "";
        }
        if (!jsonResponse.contains("choices") || !jsonResponse["choices"].is_array() || jsonResponse["choices"].empty()) {
            std::cerr << "[ERROR] API response missing 'choices' array. Full response:\n" << jsonStr << std::endl;
            return "";
        }
        if (!jsonResponse["choices"][0].contains("message") || !jsonResponse["choices"][0]["message"].contains("content")) {
            std::cerr << "[ERROR] API response missing 'message.content'. Full response:\n" << jsonStr << std::endl;
            return "";
        }
        std::string response = jsonResponse["choices"][0]["message"]["content"];
        return response;
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] Failed to parse API response: " << e.what() << "\nFull response:\n" << jsonStr << std::endl;
        return "";
    }
}

size_t _writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}
