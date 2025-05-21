#include <gtest/gtest.h>
#include "chathistory.hpp"

TEST(ChatHistoryTest, AddDialogIncreasesSizeAndContent) {
    ChatHistory history;
    EXPECT_EQ(history.toString().empty(), true);
    history.addDialog("user", "Hello!");
    EXPECT_EQ(history.toString().empty(), false);
    EXPECT_EQ(history.toString(), "user: Hello!\n");
}

TEST(ChatHistoryTest, AddMultipleDialogsContentAndOrder) {
    ChatHistory history;
    history.addDialog("user", "Hello!");
    history.addDialog("assistant", "Hi there!");
    history.addDialog("user", "How are you?");
    EXPECT_EQ(history.toString(), "user: Hello!\nassistant: Hi there!\nuser: How are you?\n");
}

TEST(ChatHistoryTest, RemoveLastDialogEmptiesHistory) {
    ChatHistory history;
    history.addDialog("user", "Hello!");
    history.removeLastDialog();
    EXPECT_EQ(history.toString().empty(), true);
}

TEST(ChatHistoryTest, RemoveLastDialogFromEmptyHistory) {
    ChatHistory history;
    // Expect no crash or error
    EXPECT_NO_THROW(history.removeLastDialog());
    EXPECT_EQ(history.toString().empty(), true);
}

TEST(ChatHistoryTest, RemoveLastDialogFromMultipleDialogs) {
    ChatHistory history;
    history.addDialog("user", "First message");
    history.addDialog("assistant", "Second message");
    history.addDialog("user", "Third message");
    history.removeLastDialog();
    EXPECT_EQ(history.toString(), "user: First message\nassistant: Second message\n");
}


TEST(ChatHistoryTest, ClearHistoryEmptiesHistory) {
    ChatHistory history;
    history.addDialog("user", "Hello!");
    history.addDialog("assistant", "Hi!");
    history.clearHistory();
    EXPECT_EQ(history.toString().empty(), true);
}

TEST(ChatHistoryTest, ToStringBasicFormatting) {
    ChatHistory history;
    history.addDialog("user", "Hello");
    history.addDialog("assistant", "Hi");
    EXPECT_EQ(history.toString(), "user: Hello\nassistant: Hi\n");
}

// Add more tests as you expand functionality!
