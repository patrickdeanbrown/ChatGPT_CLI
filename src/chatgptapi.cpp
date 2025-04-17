// chatgptapi.cpp
//
// Wrapper for calling ChatGPT API

#include "chatgptapi.hpp"
#include "chathistory.hpp"
#include "request.hpp"

// Implementation with dependency injection
void callChatGPTAPI(const std::string &input, ChatHistory &chatHistory, RequestFn requestFn) {
    std::string apiResponse = requestFn(input, chatHistory);
    std::string chatGPTResponseContent = getChatGPTResponseContent(apiResponse);

    chatHistory.printLastDialog(); // prints the user's input
    chatHistory.addDialog("assistant", chatGPTResponseContent);
    chatHistory.printLastDialog(); // prints the content just returned from ChatGPT
}

// Overload with default argument
void callChatGPTAPI(const std::string &input, ChatHistory &chatHistory) {
    callChatGPTAPI(input, chatHistory, makeRequest);
}
