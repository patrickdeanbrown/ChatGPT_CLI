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
    void addDialog(const std::string& participantName, const std::string& message);
    void removeLastDialog();
    void printLastDialog() const;
    void clearHistory();
    void printHistory() const;
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
