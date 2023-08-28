//  filereadwrite.hpp
//
// File reading and writing utilities

#ifndef filereadwrite_hpp
#define filereadwrite_hpp

#include <string>

/// @brief Returns the current working directory as a std::string
///
/// @return std::string the current working directory
std::string getCurrentWorkingDirectory();

/// @brief Opens a file in write mode and returns an output file stream
///
/// @returns std::ofstream an output file stream of the file
std::ofstream openFileForWriting(const std::string &filename);

/// @brief Writes content to a file
///
/// @param filename const std::string& filename of the file to open and write to
/// @param content const std::string& the content to write to the file
void writeToFile(const std::string &filename, const std::string &content);

/// @brief Opens a file and reads the contents into an std::string
///
/// @param filename const std::string the name of the file to open and read
///
/// @return std::string the content of the file
std::string readFileToString(const std::string filename);

#endif /* filereadwrite_hpp */
