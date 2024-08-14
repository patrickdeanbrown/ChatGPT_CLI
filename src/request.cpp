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
    payload["model"] = "chatgpt-4o-latest";

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

        // get API KEY
        const char *api_key = std::getenv("OPENAI_KEY");
        if (api_key == nullptr)
        {
            std::cerr << "OPENAI_KEY environment variable not set." << std::endl;
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
    nlohmann::json jsonResponse = nlohmann::json::parse(jsonStr);
    std::string response = jsonResponse["choices"][0]["message"]["content"];
    return response;
}

size_t _writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}
