// ChatGPT CLI - A CLI interface for chatting with ChatGPT
// Copyright (C) 2025 - Patrick Brown

#include "chatgptapi.hpp"
#include "command.hpp"
#include "commandcontext.hpp"
#include "apikeycheck.hpp"
#include "chathistory.hpp" // Ensure ChatHistory is included
#include <iostream>
// #include <string> // Already included by ftxui headers indirectly
// #include <termcolor/termcolor.hpp> // No longer needed for main output

// FTXUI Headers
#include <ftxui/component/screen_interactive.hpp> // For ScreenInteractive
#include <ftxui/component/component.hpp>         // For Component, Renderer, Vertical, Horizontal
#include <ftxui/component/component_options.hpp> // For InputOption and other component options
#include <ftxui/dom/elements.hpp>               // For text, vbox, hbox, border, flex, separator, paragraph
#include <ftxui/screen/color.hpp>               // For ftxui::Color
#include <string>                               // For std::string

// Global FTXUI Components and Data
std::string userInput;
ftxui::Component inputComponent;
ftxui::Component historyComponent;
ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen().WithMouse();

/**
 * @brief Entry point for the ChatGPT CLI application.
 *
 * Initializes the environment, validates the OpenAI API key,
 * and runs the main user input loop using FTXUI.
 *
 * @return int Exit code (0 for normal termination).
 */
int main()
{
    // Check if the OpenAI API key is valid before starting the CLI
    checkOpenAIKeyOrExit();
    CommandContext commandContext; 
    ChatHistory chatHistory;       // Actual chat history store
    int historyPaneSize{20};

    // Input component options and on_enter handler
    auto input_option = ftxui::InputOption();
    input_option.on_enter = [&] {
        if (userInput.empty()) {
            return; // Do nothing if input is empty
        }

        std::string originalUserInput = userInput; // Store before clearing

        // Add user input to the actual ChatHistory
        // chatHistory.addDialog("user", originalUserInput); // Disabled: makeRequest now handles this

        // Clear the input field before processing, so UI feels responsive
        userInput.clear(); 

        // Process the command or API call
        if (!originalUserInput.empty()) { // Double check, though first check should catch it
            if (originalUserInput[0] == '%') {
                try {
                    commandContext.setCommandAndArgs(originalUserInput);
                    // handleCommand is expected to add its output/errors to chatHistory
                    handleCommand(commandContext, chatHistory);
                } catch (const std::exception& e) {
                    // If setCommandAndArgs or handleCommand throws an exception not caught internally
                    chatHistory.addDialog("system", "Error processing command: " + std::string(e.what()));
                }
            } else {
                // Add "Assistant is thinking..." message and refresh screen
                chatHistory.addDialog("system", "Assistant is thinking...");
                screen.PostEvent(ftxui::Event::Custom); // Ensure "thinking" message is displayed

                // callChatGPTAPI is expected to add assistant's response or errors to chatHistory
                // It might also throw, e.g., if network fails.
                try {
                    // Pass the screen object for streaming updates
                    callChatGPTAPI(originalUserInput, chatHistory, &screen);
                } catch (const std::exception& e) {
                    // If callChatGPTAPI itself throws an exception (e.g., very fundamental issue, though most errors should be handled internally)
                    // First, try to remove "Assistant is thinking..." if it's still the last message
                    if (!chatHistory.isEmpty()) {
                        auto lastDialog = chatHistory.getLastDialog();
                        if (lastDialog.first == "system" && lastDialog.second == "Assistant is thinking...") {
                            chatHistory.removeLastDialog();
                        }
                    }
                    chatHistory.addDialog("system", "Critical Error calling API: " + std::string(e.what()));
                     screen.PostEvent(ftxui::Event::Custom); // Refresh to show the error
                }
            }
        }
        // The general screen.PostEvent at the end of on_enter might be redundant if callChatGPTAPI's
        // _writeCallback always posts events for stream updates, and error conditions above also post.
        // However, command handling still needs this, so it can be kept, or logic made more specific.
        // For now, specific posts have been added, and this one will ensure commands also refresh.
        screen.PostEvent(ftxui::Event::Custom); 
    };
    inputComponent = ftxui::Input(&userInput, "Enter message or command (e.g. %help, %quit)", input_option);

    // History rendering component
    historyComponent = ftxui::Renderer([&] {
        ftxui::Elements history_elements;
        for (const auto& dialog_pair : chatHistory) { // Iterate over ChatHistory
            std::string participant = dialog_pair.first;
            std::string message = dialog_pair.second;
            
            ftxui::Element element;
            if (participant == "user") {
                element = ftxui::paragraph(participant + ": " + message) | ftxui::color(ftxui::Color::Green);
            } else if (participant == "assistant") { 
                element = ftxui::paragraph(participant + ": " + message) | ftxui::color(ftxui::Color::Blue);
            } else if (participant == "system" || participant == "error") { // For command outputs or errors
                element = ftxui::paragraph(participant + ": " + message) | ftxui::color(ftxui::Color::Yellow);
            } else { 
                element = ftxui::paragraph(participant + ": " + message) | ftxui::color(ftxui::Color::GrayDark);
            }
            history_elements.push_back(element);
        }
        return ftxui::vbox(history_elements) | ftxui::yframe | ftxui::inverted;
    });

    // Layout
    auto layout = ftxui::ResizableSplitBottom(historyComponent, inputComponent, &historyPaneSize);
    layout = layout | ftxui::border; 

    // Run the FTXUI loop
    screen.Loop(layout);

    return 0;
}
