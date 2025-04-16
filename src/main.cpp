// ChatGPT CLI - A CLI interface for chatting with ChatGPT
// Copyright (C) 2023 - Patrick Brown

#include "chatgptapi.hpp"
#include "command.hpp"
#include "commandcontext.hpp"
#include "apikeycheck.hpp"
#include <iostream>
#include <string>
#include <termcolor/termcolor.hpp>

int main()
{
    // Check if the OpenAI API key is valid before starting the CLI
    checkOpenAIKeyOrExit();
    std::string commandLineInput;
    CommandContext commandContext;
    ChatHistory chatHistory;

    // Main program loop
    while (true)
    {
        std::cout << "ChatGPT> ";
        std::getline(std::cin, commandLineInput);

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
