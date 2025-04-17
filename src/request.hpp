//  request.hpp
//
// Handles curl request to ChatGPT API and response extraction

#ifndef request_hpp
#define request_hpp

#include "chathistory.hpp"
#include <string>

/**
 * @brief Calls the ChatGPT API using cURL, sending a new message and chat history for context.
 *
 * @param message The next user message to send to ChatGPT.
 * @param chatHistory The chat history to provide context for the API request.
 * @return A JSON-formatted string containing the raw response from ChatGPT.
 * @throws std::runtime_error if the request fails or the response is invalid.
 */
std::string makeRequest(const std::string &message, ChatHistory &chatHistory);

/**
 * @brief Parses a raw JSON response to extract the content returned by the ChatGPT API.
 *
 * @param jsonStr The JSON response as a string.
 * @return The assistant's message content as a string.
 * @throws std::runtime_error if parsing fails or the expected fields are missing.
 */
std::string getChatGPTResponseContent(const std::string &jsonStr);

/**
 * @brief cURL write callback to write contents of a response into a buffer.
 *
 * @param contents Pointer to the data received.
 * @param size Size of each data element.
 * @param nmemb Number of elements.
 * @param userp Pointer to the buffer where data should be written.
 * @return The number of bytes actually taken care of.
 */
size_t _writeCallback(void *contents, size_t size, size_t nmemb, void *userp);

#endif /* request_hpp */
