//  filereadwrite.hpp
//
// File reading and writing utilities

#ifndef filereadwrite_hpp
#define filereadwrite_hpp

#include <string>
#include <filesystem>
#include <fstream>

/// @brief Returns the current working directory as a std::filesystem::path
/// @return std::filesystem::path the current working directory
std::filesystem::path getCurrentWorkingDirectory();

/// @brief Opens a file in write mode and returns an output file stream
/// @param filepath Path of the file to open for writing
/// @return std::ofstream Output file stream of the file
std::ofstream openFileForWriting(const std::filesystem::path &filepath);

/// @brief Writes content to a file
/// @param filepath Path of the file to write to
/// @param content Content to write to the file
void writeToFile(const std::filesystem::path &filepath, const std::string &content);

/// @brief Opens a file and reads the contents into a string
/// @param filepath Path of the file to read
/// @return Content of the file as a string
std::string readFileToString(const std::filesystem::path &filepath);

#endif /* filereadwrite_hpp */
