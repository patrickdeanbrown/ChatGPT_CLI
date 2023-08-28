//  commandcontext.cpp
//
// CommandContext holds information about the user command and its arguments.

#include "commandcontext.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

std::string CommandContext::getCommand() const
{
    return m_command;
}

std::string CommandContext::getArgument(size_t argumentIndex) const
{
    std::string argument;
    try
    {
        argument = m_arguments.at(argumentIndex);
    }
    catch (std::out_of_range &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "Out of range error in m_arguments at index: " << argumentIndex << std::endl;
        std::cerr << "Returning empty string" << std::endl;
        return "";
    }
    return argument;
}

size_t CommandContext::getArgumentsSize() const
{
    return m_arguments.size();
}

void CommandContext::setCommandAndArgs(const std::string& rawCommandInput)
{
    m_command.clear();
    m_arguments.clear();
    _parseCommand(rawCommandInput);
}

void CommandContext::_parseCommand(const std::string& rawCommandInput)
{
    std::string token;
    std::vector<std::string> commandTokens;
    std::istringstream iss(rawCommandInput);

    while (iss >> token)
    {
        commandTokens.push_back(token);
    }

    if (commandTokens.empty())
    {
        std::cerr << "Error: Unable to parse rawCommandInput. No tokens parsed." << std::endl;
        return;
    }

    try
    {
        m_command = commandTokens.at(0);
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Error: Unable to access commandTokens at index 0" << e.what() << std::endl;
        return;
    }

    try
    {
        for (auto it = commandTokens.begin() + 1; it != commandTokens.end();
             ++it) // index 1 is the first possible argument to "%command"
        {
            m_arguments.push_back(*it);
        }
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Error: Index error when accessing commandTokens." << e.what() << std::endl;
        return;
    }
}
