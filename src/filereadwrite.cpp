//  filereadwrite.cpp
//
// File reading and writing utilities

#include "filereadwrite.hpp"
#include <iostream>
#include <sstream>
#include <filesystem>

std::filesystem::path getCurrentWorkingDirectory()
{
    try {
        return std::filesystem::current_path();
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error getting current working directory: " << e.what() << std::endl;
        return {};
    }
}

std::ofstream openFileForWriting(const std::filesystem::path &filepath)
{
    std::ofstream file(filepath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filepath << std::endl;
    }
    return file;
}

void writeToFile(const std::filesystem::path &filepath, const std::string &content)
{
    std::ofstream file = openFileForWriting(filepath);
    if (file.is_open())
    {
        file << content;
        file.close();
    }
}

std::string readFileToString(const std::filesystem::path &filepath)
{
    // Read the entire file into the string using a string stream
    std::ostringstream ss;
    std::ifstream ifs(filepath);

    if (!ifs.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filepath.string());
    }

    ss << ifs.rdbuf();
    ifs.close();

    return ss.str();
}
