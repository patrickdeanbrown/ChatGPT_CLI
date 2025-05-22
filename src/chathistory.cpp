//  chathistory.cpp
//
// Stores and manipulates a record of user and agent dialogs with/from ChatGPT

#include "chathistory.hpp"
#include "formatting.hpp" // Keep if still used by other functions, or remove if not. For now, assuming it might be used by something not being deleted.
#include <iostream> // Kept for std::cerr in addDialog and removeLastDialog
#include <string>
// #include <termcolor/termcolor.hpp> // Removed

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

std::string ChatHistory::toString() const
{
    std::string output;
    for (const auto &[role, response] : m_chatHistory)
    {
        output.append(role + ": " + response + "\n"); 
    }

    return output;
}

// printFormatted function removed
// ChatHistory::printHistory method removed
// ChatHistory::printLastDialog method removed
