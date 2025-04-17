// ChatGPT CLI - A CLI interface for chatting with ChatGPT
// Copyright (C) 2023 - Patrick Brown

#include "chatgptapi.hpp"
#include "command.hpp"
#include "commandcontext.hpp"
#include "apikeycheck.hpp"
#include <iostream>
#include <string>
#include <termcolor/termcolor.hpp>
#include "linenoise.h" // Added for improved line editing

/**
 * @brief Entry point for the ChatGPT CLI application.
 *
 * Initializes the environment, validates the OpenAI API key,
 * and runs the main user input loop, handling commands and chat requests.
 *
 * @return int Exit code (0 for normal termination).
 */
int main()
{
    // Check if the OpenAI API key is valid before starting the CLI
    checkOpenAIKeyOrExit();
    CommandContext commandContext;
    ChatHistory chatHistory;

    // Main program loop
    while (true)
    {
        // Use linenoise for line editing and history
        char* input = linenoise("ChatGPT> ");
        if (input == nullptr) {
            std::cout << std::endl;
            break; // EOF (Ctrl-D)
        }
        std::string commandLineInput(input);
        linenoiseFree(input);

        if (!commandLineInput.empty() && commandLineInput[0] == '%')
        {
            try
            {
                commandContext.setCommandAndArgs(commandLineInput);
                handleCommand(commandContext, chatHistory);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
                std::cerr << "Error found. Retry input." << std::endl;
            }
            continue;
        }
        callChatGPTAPI(commandLineInput, chatHistory);
    }

    return 0;
}
