//  request.hpp
//
// Handles curl request to ChatGPT API and response extraction

#ifndef request_hpp
#define request_hpp

#include "chathistory.hpp"
#include <string>

/// @brief Calls ChatGPT API using cURL passing the API both a new message and the chat history for context
///
/// @param message const std::string& the next user message to pass to ChatGPT
/// @param chatHistory ChatHistory& the chat history to pass to ChatGPT for context
///
/// @return std::string JSON formatted string containing the raw response from ChatGPT
std::string makeRequest(const std::string &message, ChatHistory &chatHistory);

/// @brief Parses raw json to extract content returned by the ChatGPT API
///
/// @param jsonStr std::string& JSON object stored as a string to be parsed
///
/// @return std::string containing the context of the ChatGPT API response
std::string getChatGPTResponseContent(const std::string &jsonStr);

/// @brief Supports cURL to write contents of request into a buffer
///
/// @param contents void pointer to the contents of the request response, typically a char buffer
/// @param size size_t size in bytes of the object making up contents, typically sizeof(char)
/// @param nmemb size_t number of objects in contents
/// @param userp void pointer to the object where contents will be written to, typically std::string or char buffer
///
/// @return size_t of the number of bytes written
size_t _writeCallback(void *contents, size_t size, size_t nmemb, void *userp);

#endif /* request_hpp */
