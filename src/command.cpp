//
// command.cpp
//
// Handlers for parsing and executing user commands for special functionality

#include "command.hpp"
#include "chathistory.hpp"
#include "commandcontext.hpp"
#include "filereadwrite.hpp"
#include "formatting.hpp" // For std::setw, std::left if used in help construction
#include <cstdlib>
#include <fstream>
#include <sstream> // For std::ostringstream
#include <stdexcept>
#include <string>
// #include <termcolor/termcolor.hpp> // No longer needed
#include <vector>
#include <iomanip> // For std::setw, std::left

void handleCommand(const CommandContext &commandContext, ChatHistory &chatHistory)
{
    std::string command = commandContext.getCommand();
    if (command == "%save")
    {
        std::string outputfileName;
        try
        {
            outputfileName = commandContext.getArgument(0);
        }
        catch (const std::out_of_range &e)
        {
            outputfileName = "outfile.txt"; // Default filename
            chatHistory.addDialog("system", "No filename provided for %save. Using default: " + outputfileName);
        }
        saveCommand(outputfileName, chatHistory);
    }
    else if (command == "%readfile")
    {
        std::string inputFilename;
        try
        {
            inputFilename = commandContext.getArgument(0);
        }
        catch (const std::out_of_range &e)
        {
            chatHistory.addDialog("error", "No filename provided for %readfile command.");
            return;
        }
        readfileCommand(inputFilename, chatHistory);
    }
    else if (command == "%clear")
    {
        clearCommand(chatHistory);
    }
    else if (command == "%deletelast")
    {
        deletelastCommand(chatHistory);
    }
    else if (command == "%printhistory")
    {
        printhistoryCommand(chatHistory);
    }
    else if (command == "%help")
    {
        helpCommand(chatHistory); // Pass chatHistory to helpCommand
    }
    else if (command == "%quit")
    {
        quitCommand();
    }
    else
    {
        chatHistory.addDialog("error", "Unknown command: " + command + ". Type %help for a list of commands.");
    }
}

void saveCommand(const std::string &outputFilename, const ChatHistory &chatHistory)
{
    try
    {
        writeToFile(outputFilename, chatHistory.toString());
        chatHistory.addDialog("system", "Chat history saved to " + outputFilename);
    }
    catch (const std::exception &e)
    {
        chatHistory.addDialog("error", "Error saving chat history to " + outputFilename + ": " + e.what());
    }
}

void readfileCommand(const std::string &inputFilename, ChatHistory &chatHistory)
{
    try
    {
        std::string fileContent = readFileToString(inputFilename);
        chatHistory.addDialog("user", fileContent); // As per original logic, file content is added as user dialog
        chatHistory.addDialog("system", "Content from " + inputFilename + " added to chat history as a user message.");
    }
    catch (const std::exception &e)
    {
        chatHistory.addDialog("error", "Error reading file " + inputFilename + ": " + e.what());
    }
}

void clearCommand(ChatHistory &chatHistory)
{
    chatHistory.clearHistory();
    chatHistory.addDialog("system", "Chat history cleared.");
}

void deletelastCommand(ChatHistory &chatHistory)
{
    // Consider checking if history was empty before removing, though removeLastDialog is safe.
    // For simplicity, always add a confirmation.
    chatHistory.removeLastDialog();
    chatHistory.addDialog("system", "Last dialog entry removed.");
}

void printhistoryCommand(const ChatHistory &chatHistory)
{
    // chatHistory.printHistory(); // Original call removed
    chatHistory.addDialog("system", "Chat history is displayed in the pane above.");
}

void quitCommand()
{
    std::exit(0);
}

void helpCommand(ChatHistory &chatHistory) // Added chatHistory parameter
{
    const int maxWidth = 20; // Adjusted for typical chat display
    std::ostringstream help_oss;
    help_oss << "***** HELP MENU *****\n\n"; // Use \n for newlines
    help_oss << std::left << std::setw(maxWidth) << "%save [filename]" << "Saves your chat as a file.\n";
    help_oss << std::left << std::setw(maxWidth) << "%readfile [filename]" << "Reads a file into history as user message.\n";
    help_oss << std::left << std::setw(maxWidth) << "%clear" << "Clears the chat history.\n";
    help_oss << std::left << std::setw(maxWidth) << "%deletelast" << "Deletes the last record in chat history.\n";
    help_oss << std::left << std::setw(maxWidth) << "%printhistory" << "Shows this message (history is above).\n";
    help_oss << std::left << std::setw(maxWidth) << "%quit" << "Exits the program.\n";
    help_oss << std::left << std::setw(maxWidth) << "%help" << "Prints this help menu.\n";
    
    chatHistory.addDialog("system", help_oss.str());
}
