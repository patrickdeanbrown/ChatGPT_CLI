//  chatgptapi.hpp
//
// Wrapper for calling ChatGPT API

#ifndef chatgptapi_hpp
#define chatgptapi_hpp

#include "chathistory.hpp"
#include <string>
#include <functional>

using RequestFn = std::function<std::string(const std::string&, ChatHistory&)>;


/**
 * @brief Sends a user message to the ChatGPT API (or mock) and handles the response.
 *
 * Calls the ChatGPT API (or a mock implementation) with the provided user input and the current chat history.
 * Stores the assistant's response in the chat history and prints both the user input
 * and the assistant's response to the terminal.
 *
 * @param input The user’s input message to send to the ChatGPT API.
 * @param chatHistory The chat history object to provide context and store the new response.
 * @param requestFn The API request function to use (default: makeRequest).
 */
void callChatGPTAPI(const std::string &input, ChatHistory &chatHistory, RequestFn requestFn);
// Overload for backward compatibility
void callChatGPTAPI(const std::string &input, ChatHistory &chatHistory);

#endif /* chatgptapi_hpp */
