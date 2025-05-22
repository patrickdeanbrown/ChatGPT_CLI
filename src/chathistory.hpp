//  chathistory.hpp
//
// Stores and manipulates a record of user and agent dialogs with/from ChatGPT

#ifndef chathistory_hpp
#define chathistory_hpp

#include <string>
#include <vector>

/// @class ChatHistory
/// @brief Stores and manipulates a record of user and agent dialogs with/from ChatGPT
class ChatHistory
{
  public:
    /**
     * @brief Adds a dialog entry to the chat history.
     * @param participantName The name of the participant ("user" or "assistant").
     * @param message The message content to add.
     */
    void addDialog(const std::string& participantName, const std::string& message);

    /**
     * @brief Removes the last dialog entry from the chat history.
     * If the history is empty, no action is taken.
     */
    void removeLastDialog();

    /**
     * @brief Appends content to the last dialog entry if it's from the "assistant".
     * If the history is empty or the last message is not from the assistant,
     * it might add a new dialog or do nothing, depending on desired behavior.
     * For now, let's assume it only appends if the last is an assistant message.
     * @param content_chunk The piece of content to append.
     */
    void appendToLastDialog(const std::string& content_chunk);

    /**
     * @brief Gets the last dialog entry.
     * @return A pair containing the participant name and message.
     * @throws std::out_of_range if the history is empty.
     */
    std::pair<std::string, std::string> getLastDialog() const;

    /**
     * @brief Checks if the chat history is empty.
     * @return True if history is empty, false otherwise.
     */
    bool isEmpty() const;

    // printLastDialog() declaration removed

    /**
     * @brief Clears all dialog entries from the chat history.
     */
    void clearHistory();

    // printHistory() declaration removed

    /**
     * @brief Converts the chat history to a formatted string.
     * @return A string representation of all chat entries.
     */
    std::string toString() const;

    /// @class iterator.
    /// @brief A helper class to allow ChatHistory to be used in for each loops.
    class iterator
    {
      private:
        using PairIterator =
            typename std::vector<std::pair<std::string, std::string>>::iterator; // iterator for m_chatHistory
        PairIterator it;

      public:
        iterator(PairIterator iterator) : it(iterator)
        {
        }

        bool operator!=(const iterator &other) const
        {
            return it != other.it;
        }

        void operator++()
        {
            ++it;
        }

        auto operator*() const
        {
            return *it;
        }
    };

    iterator begin()
    {
        return iterator(m_chatHistory.begin());
    }

    iterator end()
    {
        return iterator(m_chatHistory.end());
    }

  private:
    std::vector<std::pair<std::string, std::string>> m_chatHistory;
};

// printFormatted() declaration removed

#endif /* chathistory_hpp */
