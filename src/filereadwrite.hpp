//  filereadwrite.hpp
//
// File reading and writing utilities

#ifndef filereadwrite_hpp
#define filereadwrite_hpp

#include <string>
#include <filesystem>
#include <fstream>

/**
 * @brief Returns the current working directory as a std::filesystem::path.
 * @return The current working directory.
 */
std::filesystem::path getCurrentWorkingDirectory();

/**
 * @brief Opens a file for writing and returns an output file stream.
 * @param filepath The path of the file to open.
 * @return An output file stream for the specified file.
 * @throws std::ios_base::failure If the file cannot be opened.
 */
std::ofstream openFileForWriting(const std::filesystem::path &filepath);

/**
 * @brief Writes content to a file.
 * @param filepath The path of the file to write to.
 * @param content The content to write to the file.
 * @throws std::ios_base::failure If the file cannot be written.
 */
void writeToFile(const std::filesystem::path &filepath, const std::string &content);

/**
 * @brief Opens a file and reads the contents into a string.
 * @param filepath The path of the file to read.
 * @return The content of the file as a string.
 * @throws std::ios_base::failure If the file cannot be read.
 */
std::string readFileToString(const std::filesystem::path &filepath);

#endif /* filereadwrite_hpp */
