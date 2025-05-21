//  chathistory.cpp
//
// Stores and manipulates a record of user and agent dialogs with/from ChatGPT

#include "chathistory.hpp"
#include "formatting.hpp"
#include <iostream>
#include <string>
#include <termcolor/termcolor.hpp>

void ChatHistory::addDialog(const std::string &participantName, const std::string &message)
{
    if (message.empty())
    {
        std::cerr << "Unable to add to ChatHistory. message is empty." << std::endl;
        return;
    }
    m_chatHistory.push_back({participantName, message});
}

void ChatHistory::removeLastDialog()
{
    if (m_chatHistory.empty())
    {
        std::cerr << "ChatHistory is empty. Cannot remove last dialog." << std::endl;
        return;
    }
    m_chatHistory.pop_back();
}

void ChatHistory::clearHistory()
{
    m_chatHistory.clear();
}

void ChatHistory::printHistory() const
{
    if (m_chatHistory.empty())
    {
        std::cerr << "ChatHistory is empty. Unable to print." << std::endl;
    }
    for (const auto &chatItem : m_chatHistory)
    {
        printFormatted(chatItem);
    }
}

std::string ChatHistory::toString() const
{
    std::string output;
    for (const auto &[role, response] : m_chatHistory)
    {
        output.append(role + ": " + response + "\n"); // Corrected format
    }

    return output;
}

void ChatHistory::printLastDialog() const
{
    if (m_chatHistory.empty())
    {
        std::cerr << "ChatHistory is empty. Unable to print last dialog." << std::endl;
        return; // Prevent further execution if history is empty
    }
    printFormatted(m_chatHistory.back());
}

void printFormatted(const std::pair<std::string, std::string> &chatItem)
{
    std::string name = chatItem.first;
    std::string content = chatItem.second;

    if (name == "user")
    {
        std::cout << termcolor::green << "User:" << std::endl;
    }
    else
    {
        std::cout << termcolor::blue << "ChatGPT:" << std::endl;
    }
    wrap(content, 72, std::cout, 4);
    std::cout << termcolor::reset << std::endl;
}
