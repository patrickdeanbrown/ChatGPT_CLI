// apikeycheck.cpp
//
// Implementation of API key validity check for OpenAI API.
#include "apikeycheck.hpp"
#include <cstdlib>
#include <curl/curl.h>
#include <iostream>
#include <string>

void checkOpenAIKeyOrExit() {
    const char *api_key = std::getenv("OPENAI_KEY");
    if (api_key == nullptr || std::string(api_key).empty()) {
        std::cerr << "[CRITICAL ERROR] Your OpenAI API key (OPENAI_KEY) is not set.\n"
                  << "Please update your API key by setting the OPENAI_KEY environment variable to a valid key.\n"
                  << "Visit https://platform.openai.com/account/api-keys to create or view your API keys.\nExiting program." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    CURL *curl = curl_easy_init();
    if (!curl) {
        std::cerr << "[CRITICAL ERROR] Failed to initialize CURL for API key check. Exiting program." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    struct curl_slist *headers = nullptr;
    std::string auth_header = "Authorization: Bearer " + std::string(api_key);
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, auth_header.c_str());
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/models");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L); // HEAD request is enough

    CURLcode res = curl_easy_perform(curl);
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    if (res != CURLE_OK || http_code != 200) {
        std::cerr << "[CRITICAL ERROR] Your OpenAI API key (OPENAI_KEY) is invalid or inactive.\n"
                  << "Please update your API key by setting the OPENAI_KEY environment variable to a valid key.\n"
                  << "Visit https://platform.openai.com/account/api-keys to create or view your API keys.\nExiting program." << std::endl;
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
        std::exit(EXIT_FAILURE);
    }
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
}
