// chatgptapi.cpp
//
// Wrapper for calling ChatGPT API

#include "chatgptapi.hpp"
#include "chathistory.hpp"
#include "request.hpp" // For makeRequest and getChatGPTResponseContent
#include "ftxui/component/screen_interactive.hpp" // For ftxui::ScreenInteractive (though already included via request.hpp)
#include <iostream> // For std::cerr (optional, for logging if needed)

void callChatGPTAPI(const std::string &input, ChatHistory &chatHistory, ftxui::ScreenInteractive* screen) {
    // Note: The user's input message is added to chatHistory by makeRequest itself.
    
    std::string apiResult = makeRequest(input, chatHistory, screen); 
    
    if (!apiResult.empty()) {
        // If makeRequest returned a non-empty string, it's likely an error JSON
        // that occurred before streaming could start (e.g., API key issue, network problem).
        std::string errorContent = getChatGPTResponseContent(apiResult); // Try to parse it
        
        if (!errorContent.empty() && errorContent.rfind("[API Error]", 0) == 0) {
            // If getChatGPTResponseContent successfully parsed an error or prefixed its own
            chatHistory.addDialog("system", errorContent); // Use the parsed/prefixed error
        } else if (!errorContent.empty()) {
            // If it's some other content (less likely for errors, but possible)
            chatHistory.addDialog("system", "API Error: " + errorContent);
        }
        else {
            // If apiResult was not empty, but getChatGPTResponseContent returned empty (e.g. malformed JSON from proxy/network)
            chatHistory.addDialog("system", "API Error: Received an malformed or unexpected response from the server during setup. Raw response: " + apiResult);
        }
        
        // Refresh the screen to show this error message from setup
        if (screen) {
            screen->PostEvent(ftxui::Event::Custom);
        }
    }
    // If apiResult is empty, it means streaming started successfully (or is expected to).
    // The _writeCallback in request.cpp will handle adding assistant messages or stream errors to chatHistory.
}
