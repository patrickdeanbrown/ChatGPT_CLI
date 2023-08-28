//  command.hpp
//
// Handlers for parsing and executing user commands for special functionality

#ifndef command_hpp
#define command_hpp

#include "chathistory.hpp"
#include "commandcontext.hpp"
#include <string>

/// @brief Determines which command function to enter based on user input and executes the
/// appropriate command
///
/// @param commandContext CommandContext& contains command and the command's arguments
/// @param chatHistory ChatHistory& contains chat history
void handleCommand(const CommandContext &commandContext, ChatHistory &chatHistory);

/// @brief Saves the chat history to a file in the current working directory
///
/// @param outputFilename const std::string& the name of the file to write
/// @param chatHistory ChatHistory& the chat history to write to the output file
void saveCommand(const std::string &outputFilename, const ChatHistory &chatHistory);

/// @brief Reads a file and adds the file as a user dialog to chatHistory
///
/// @param inputFilename const std::string& the file to read into chatHistory
/// @param chatHistory ChatHistory& the chat history to update with the contents of the file read in
void readfileCommand(const std::string &inputFilename, ChatHistory &chatHistory);

/// @brief Deletes all prior entries in chatHistory
///
/// @param chatHistory ChatHistory& the ChatHistory to clear of all entries
void clearCommand(ChatHistory &chatHistory);

/// @brief Deletes (pops) the most recent entry in chatHistory
///
/// @param chatHistory ChatHistory& the ChatHistory where the last entry will be deleted
void deletelastCommand(ChatHistory &chatHistory);

/// @brief Pretty prints the entire chat history
///
/// @param chatHistory ChatHistory& the ChatHistory to print
void printhistoryCommand(const ChatHistory &chatHistory);

/// @brief Exits the program
void quitCommand();

/// @brief Prints a table of possible commands and their functionality
void helpCommand();

#endif /* command_hpp */
