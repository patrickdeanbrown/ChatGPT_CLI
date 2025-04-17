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
     * @brief Prints the most recent dialog entry to the console.
     * If the history is empty, prints a warning.
     */
    void printLastDialog() const;

    /**
     * @brief Clears all dialog entries from the chat history.
     */
    void clearHistory();

    /**
     * @brief Prints the entire chat history to the console.
     * If the history is empty, prints a warning.
     */
    void printHistory() const;

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

/// @brief Pretty prints a single chat dialog, a pair of the chat participant ("user" or "agent") and their response.
///
/// @param chatDialog &std::pair<std::string, std::string> a single entry in a ChatHistory that is a pair of
/// the chat participant ("user" or "agent") and their response as std::string.
void printFormatted(const std::pair<std::string, std::string> &chatDialog);

#endif /* chathistory_hpp */
