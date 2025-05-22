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

bool ChatHistory::isEmpty() const
{
    return m_chatHistory.empty();
}

std::pair<std::string, std::string> ChatHistory::getLastDialog() const
{
    if (m_chatHistory.empty())
    {
        throw std::out_of_range("Chat history is empty");
    }
    return m_chatHistory.back();
}

void ChatHistory::appendToLastDialog(const std::string &content_chunk)
{
    if (m_chatHistory.empty())
    {
        // Optionally: Add as new dialog if history is empty and it's an assistant message
        // For now, do nothing or log if this case is unexpected.
        std::cerr << "Cannot append: Chat history is empty." << std::endl;
        return;
    }

    std::pair<std::string, std::string> &lastDialog = m_chatHistory.back();
    // Only append if the last message is from the "assistant"
    // And if the chunk is not empty
    if (lastDialog.first == "assistant" && !content_chunk.empty())
    {
        lastDialog.second += content_chunk;
    }
    else if (lastDialog.first != "assistant")
    {
        std::cerr << "Cannot append: Last message not from assistant." << std::endl;
        // Fallback: could add a new dialog if desired:
        // addDialog("assistant", content_chunk);
    }
    // If content_chunk is empty, do nothing.
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
