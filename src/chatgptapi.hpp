//  chatgptapi.hpp
//
// Wrapper for calling ChatGPT API

#ifndef chatgptapi_hpp
#define chatgptapi_hpp

#include "chathistory.hpp"
#include <string>
// #include <functional> // No longer needed for RequestFn
// Forward declare ftxui::ScreenInteractive to avoid including the full header here if possible,
// but since request.hpp (which chatgptapi.cpp will include) already includes it, it's fine.
namespace ftxui {
    class ScreenInteractive;
}

/**
 * @brief Sends a user message to the ChatGPT API and handles the response, supporting streaming.
 *
 * Calls the ChatGPT API with the provided user input and the current chat history.
 * For streaming responses, the chat history is updated incrementally by the callback mechanism
 * in `makeRequest`. If `makeRequest` returns an error payload immediately (e.g. bad API key),
 * this function handles adding that error to the chat history.
 *
 * @param input The user’s input message to send to the ChatGPT API.
 * @param chatHistory The chat history object to provide context and store the new response.
 * @param screen A pointer to the ftxui::ScreenInteractive instance for UI refresh during streaming.
 */
void callChatGPTAPI(const std::string &input, ChatHistory &chatHistory, ftxui::ScreenInteractive* screen);

#endif /* chatgptapi_hpp */
