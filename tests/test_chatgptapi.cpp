#include <gtest/gtest.h>
#include "chatgptapi.hpp"
#include "chathistory.hpp"
#include <string>

// Mock request function to simulate OpenAI API response
std::string mockRequest(const std::string& input, ChatHistory& chatHistory) {
    // Simulate a JSON response with a fixed assistant reply
    return R"({\"choices\":[{\"message\":{\"content\":\"Mocked response for: " + input + R"\"}}]})";
}

// Mock getChatGPTResponseContent for full isolation (optional, but here we use the real one)

TEST(ChatGPTAPITest, HandlesMockedAPIResponse) {
    ChatHistory history;
    history.addDialog("user", "Hello?");
    // The mock will return a canned JSON string
    callChatGPTAPI("Hello?", history, mockRequest);
    std::string output = history.toString();
    // Should contain both user and assistant reply
    EXPECT_NE(output.find("user"), std::string::npos);
    EXPECT_NE(output.find("assistant"), std::string::npos);
    EXPECT_NE(output.find("Mocked response for: Hello?"), std::string::npos);
}

// You can add more tests for error cases, empty input, etc.
