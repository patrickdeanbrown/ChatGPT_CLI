// chatgptapi.cpp
//
// Wrapper for calling ChatGPT API

#include "chatgptapi.hpp"
#include "chathistory.hpp"
#include "request.hpp"

void callChatGPTAPI(const std::string &input, ChatHistory &chatHistory)
{
    std::string apiResponse = makeRequest(input, chatHistory);
    std::string chatGPTResponseContent = getChatGPTResponseContent(apiResponse);

    chatHistory.printLastDialog(); // prints the user's input
    chatHistory.addDialog("assistant", chatGPTResponseContent);
    chatHistory.printLastDialog(); // prints the content just returned from ChatGPT
}
