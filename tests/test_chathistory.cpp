#include <gtest/gtest.h>
#include "chathistory.hpp"

TEST(ChatHistoryTest, AddDialogIncreasesSize) {
    ChatHistory history;
    EXPECT_EQ(history.toString().empty(), true);
    history.addDialog("user", "Hello!");
    EXPECT_EQ(history.toString().empty(), false);
}

TEST(ChatHistoryTest, RemoveLastDialogEmptiesHistory) {
    ChatHistory history;
    history.addDialog("user", "Hello!");
    history.removeLastDialog();
    EXPECT_EQ(history.toString().empty(), true);
}

TEST(ChatHistoryTest, ClearHistoryEmptiesHistory) {
    ChatHistory history;
    history.addDialog("user", "Hello!");
    history.addDialog("assistant", "Hi!");
    history.clearHistory();
    EXPECT_EQ(history.toString().empty(), true);
}

// Add more tests as you expand functionality!
