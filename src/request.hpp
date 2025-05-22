//  request.hpp
//
// Handles curl request to ChatGPT API and response extraction

#ifndef request_hpp
#define request_hpp

#include "chathistory.hpp"
#include <string>
#include "ftxui/component/screen_interactive.hpp" // Required for ftxui::ScreenInteractive

// Forward declaration of ChatHistory can be used if chathistory.hpp is heavy,
// but for a pointer type, full include is often fine.
// class ChatHistory; 

struct StreamCallbackData {
    ChatHistory* chatHistory;
    ftxui::ScreenInteractive* screen;
    std::string currentAssistantResponse; // Used to accumulate parts of the assistant's message
    bool assistantMessageAdded;       // Tracks if the first chunk of the assistant's message has been added to ChatHistory
    // std::string currentAssistantMessageId; // Not strictly needed if we append to last or replace last
};

/**
 * @brief Calls the ChatGPT API using cURL, sending a new message and chat history for context.
 *        Supports streaming responses.
 *
 * @param message The next user message to send to ChatGPT.
 * @param chatHistory The chat history to provide context for the API request.
 * @param screen Pointer to the FTXUI screen for posting refresh events during streaming.
 * @return A JSON-formatted string (potentially empty or summary if streaming handled by callback)
 *         or an error message if the initial request setup fails.
 * @throws std::runtime_error if the request fails or the response is invalid.
 */
std::string makeRequest(const std::string &message, ChatHistory &chatHistory, ftxui::ScreenInteractive* screen);

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
