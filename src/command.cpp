//
// command.cpp
//
// Handlers for parsing and executing user commands for special functionality

#include "command.hpp"
#include "chathistory.hpp"
#include "commandcontext.hpp"
#include "filereadwrite.hpp"
#include "formatting.hpp"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <termcolor/termcolor.hpp>
#include <vector>

void handleCommand(const CommandContext &commandContext, ChatHistory &chatHistory)
{
    if (commandContext.getCommand() == "%save")
    {
        std::string outputfileName;
        try
        {
            outputfileName = commandContext.getArgument(0);
        }
        catch (std::out_of_range &e)
        {
            std::cerr << "File name not correctly read as argument to %save. Using default 'outfile.txt'." << std::endl;
            outputfileName = "outfile.txt";
        }
        saveCommand(outputfileName, chatHistory);
    }
    else if (commandContext.getCommand() == "%readfile")
    {
        std::string inputFilename;
        try
        {
            inputFilename = commandContext.getArgument(0);
        }
        catch (std::out_of_range &e)
        {
            std::cerr << "File name not correctly read as argument to %readfile." << std::endl;
            return;
        }
        readfileCommand(inputFilename, chatHistory);
    }
    else if (commandContext.getCommand() == "%clear")
    {
        clearCommand(chatHistory);
    }
    else if (commandContext.getCommand() == "%deletelast")
    {
        deletelastCommand(chatHistory);
    }
    else if (commandContext.getCommand() == "%printhistory")
    {
        printhistoryCommand(chatHistory);
    }
    else if (commandContext.getCommand() == "%help")
    {
        helpCommand();
    }
    else if (commandContext.getCommand() == "%quit")
    {
        quitCommand();
    }
    else
    {
        throw std::runtime_error("Unable to parse command.");
    }
}

void saveCommand(const std::string &outputFilename, const ChatHistory &chatHistory)
{
    writeToFile(outputFilename, chatHistory.toString());
}

void readfileCommand(const std::string &inputFilename, ChatHistory &chatHistory)
{
    std::string fileContent = readFileToString(inputFilename);
    chatHistory.addDialog("user", fileContent);
}

void clearCommand(ChatHistory &chatHistory)
{
    chatHistory.clearHistory();
}

void deletelastCommand(ChatHistory &chatHistory)
{
    chatHistory.removeLastDialog();
}

void printhistoryCommand(const ChatHistory &chatHistory)
{
    chatHistory.printHistory();
}

void quitCommand()
{
    std::exit(0);
}

void helpCommand()
{
    const int maxWidth = 30;
    std::cout << "***** HELP MENU *****" << std::endl
              << std::endl;
    std::cout << std::left << std::setw(maxWidth) << "%save [filename]"
              << "Saves your chat as a file." << std::endl;
    std::cout << std::left << std::setw(maxWidth) << "%readfile [filename]"
              << "Reads in a file from the cwd." << std::endl;
    std::cout << std::left << std::setw(maxWidth) << "%clear"
              << "Clears the chat history." << std::endl;
    std::cout << std::left << std::setw(maxWidth) << "%deletelast"
              << "Deletes the last record in the chat history." << std::endl;
    std::cout << std::left << std::setw(maxWidth) << "%printhistory"
              << "Prints the chat history to the console." << std::endl;
    std::cout << std::left << std::setw(maxWidth) << "%quit"
              << "Exits the program." << std::endl;
    std::cout << std::left << std::setw(maxWidth) << "%help"
              << "Prints the help menu." << std::endl;
}
