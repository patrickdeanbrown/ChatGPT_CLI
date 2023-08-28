//  chatgptapi.hpp
//
// Wrapper for calling ChatGPT API

#ifndef chatgptapi_hpp
#define chatgptapi_hpp

#include "chathistory.hpp"
#include <string>

/// @brief Calls ChatGPT's API, stores the resulting content in chatHistory, and prints the user input
/// and ChatGPT's content to the terminal
///
/// @param input std::string& User input to be passed to the ChatGPT API
/// @param chatHistory &ChatHistory Context for calling the ChatGPT API and where the content
/// returned from ChatGPT is stored
void callChatGPTAPI(const std::string &input, ChatHistory &chatHistory);

#endif /* chatgptapi_hpp */
