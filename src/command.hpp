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
/// @param chatHistory ChatHistory& the chat history to write to the output file, modified with status messages.
void saveCommand(const std::string &outputFilename, ChatHistory &chatHistory);

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

/// @brief Adds a message to chat history indicating it's displayed above.
///
/// @param chatHistory ChatHistory& the ChatHistory to be modified with a status message.
void printhistoryCommand(ChatHistory &chatHistory);

/// @brief Exits the program
void quitCommand();

/// @brief Prints a table of possible commands and their functionality
/// @param chatHistory ChatHistory& the ChatHistory to add the help text to
void helpCommand(ChatHistory &chatHistory);

#endif /* command_hpp */
