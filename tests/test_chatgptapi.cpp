#include <gtest/gtest.h>
#include "chatgptapi.hpp"
#include "chathistory.hpp"
#include <string>
#include <nlohmann/json.hpp> // For JSON manipulation

// Mock request function to simulate OpenAI API response
std::string mockRequest(const std::string& input, ChatHistory& chatHistory) {
    // Simulate a JSON response with a fixed assistant reply
    nlohmann::json j;
    j["choices"] = nlohmann::json::array();
    nlohmann::json message_content;
    message_content["content"] = "Mocked response for: " + input;
    nlohmann::json message;
    message["message"] = message_content;
    j["choices"].push_back(message);
    return j.dump();
}

// Mock getChatGPTResponseContent for full isolation (optional, but here we use the real one)

TEST(ChatGPTAPITest, HandlesMockedAPIResponse) {
    ChatHistory history;
    history.addDialog("user", "Hello?");
    // The mock will return a canned JSON string
    // Pass nullptr for the ScreenInteractive* argument as tests don't use UI.
    callChatGPTAPI("Hello?", history, nullptr);
    std::string output = history.toString();
    // Should contain both user and assistant reply
    EXPECT_NE(output.find("user"), std::string::npos);
    EXPECT_NE(output.find("assistant"), std::string::npos);
    EXPECT_NE(output.find("Mocked response for: Hello?"), std::string::npos);
}

TEST(ChatGPTAPITest, HandlesEmptyInput) {
    ChatHistory history;
    
    std::streambuf* oldCerr = std::cerr.rdbuf();
    std::ostringstream newCerr;
    std::cerr.rdbuf(newCerr.rdbuf()); // Start redirection here

    // Attempt to add user's empty message. ChatHistory::addDialog will print to cerr and not add it.
    history.addDialog("user", ""); 
    
    // API is called with empty input.
    // callChatGPTAPI will call printLastDialog (history is empty, so it prints error and returns),
    // then add assistant's response.
    // Pass nullptr for the ScreenInteractive* argument.
    callChatGPTAPI("", history, nullptr); 
    
    std::cerr.rdbuf(oldCerr);

    std::string output = history.toString();
    std::string cerrOutput = newCerr.str();

    // Check cerr for BOTH expected messages
    EXPECT_NE(cerrOutput.find("Unable to add to ChatHistory. message is empty."), std::string::npos); 
    EXPECT_NE(cerrOutput.find("ChatHistory is empty. Unable to print last dialog."), std::string::npos); 

    // User's empty message should NOT be in the final history string from toString()
    EXPECT_EQ(output.find("user: \n"), std::string::npos); 
    
    // Assistant's response to empty input should be present
    EXPECT_NE(output.find("assistant: Mocked response for: \n"), std::string::npos); 
}

// Mock request function to simulate an OpenAI API error response
std::string mockErrorRequest(const std::string& input, ChatHistory& chatHistory) {
    nlohmann::json j_error;
    j_error["error"]["message"] = "Test API error";
    j_error["error"]["type"] = "test_error_type";
    return j_error.dump();
}

TEST(ChatGPTAPITest, HandlesAPIErrorResponse) {
    ChatHistory history;
    // User's initial message is added before callChatGPTAPI by makeRequest, 
    // but for testing callChatGPTAPI directly, we should simulate this.
    // However, callChatGPTAPI itself does not add the user message to history,
    // it relies on the requestFn (like the real makeRequest) to do it.
    // The mockRequest we use for other tests doesn't add to history.
    // The actual `makeRequest` adds the user message to history.
    // `callChatGPTAPI` then calls `chatHistory.printLastDialog()` (user)
    // then adds assistant msg, then `printLastDialog()` (assistant).

    // For this test, let's assume the user message "Error prone input" was already added
    // as `makeRequest` would do.
    history.addDialog("user", "Error prone input");
    
    // Capture cerr output
    std::streambuf* oldCerr = std::cerr.rdbuf();
    std::ostringstream newCerr;
    std::cerr.rdbuf(newCerr.rdbuf());

    // Pass nullptr for the ScreenInteractive* argument.
    callChatGPTAPI("Error prone input", history, nullptr);
    
    // Restore cerr
    std::cerr.rdbuf(oldCerr);

    std::string output = history.toString();
    // cerr should contain error messages from getChatGPTResponseContent and addDialog
    EXPECT_NE(newCerr.str().find("[OPENAI API ERROR] Test API error"), std::string::npos);
    EXPECT_NE(newCerr.str().find("Unable to add to ChatHistory. message is empty."), std::string::npos);

    // History should contain the user message but not an assistant message
    // because getChatGPTResponseContent returns "" on error, and addDialog doesn't add empty messages.
    EXPECT_NE(output.find("user: Error prone input\n"), std::string::npos);
    EXPECT_EQ(output.find("assistant:"), std::string::npos); // No assistant message added
}

// You can add more tests for error cases, empty input, etc.
