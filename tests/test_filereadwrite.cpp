#include <gtest/gtest.h>
#include "filereadwrite.hpp"
#include <fstream>
#include <filesystem>

TEST(FileReadWriteTest, WriteAndReadBack) {
    std::string testFile = "testfile.txt";
    std::string content = "Hello, world!";
    openFileForWriting(testFile); // Should create or truncate
    writeToFile(testFile, content);
    std::string readContent = readFileToString(testFile);
    EXPECT_EQ(content, readContent);
    std::filesystem::remove(testFile);
}

TEST(FileReadWriteTest, ReadNonExistentFileThrows) {
    EXPECT_THROW(readFileToString("nonexistent.txt"), std::runtime_error);
}

TEST(FileReadWriteTest, WriteEmptyContent) {
    std::string testFile = "emptyfile.txt";
    openFileForWriting(testFile);
    writeToFile(testFile, "");
    std::string readContent = readFileToString(testFile);
    EXPECT_EQ(readContent, "");
    std::filesystem::remove(testFile);
}
