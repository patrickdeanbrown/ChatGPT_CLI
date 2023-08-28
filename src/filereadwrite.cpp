//  filereadwrite.hpp
//
// File reading and writing utilities

#include "filereadwrite.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>

std::string getCurrentWorkingDirectory()
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != nullptr)
    {
        return std::string(cwd);
    }
    else
    {
        std::cerr << "Error getting current working directory" << std::endl;
        return "";
    }
}

std::ofstream openFileForWriting(const std::string &filename)
{
    std::string path = getCurrentWorkingDirectory() + "/" + filename;
    std::ofstream file(path);
    if (!file.is_open())
    {
        std::cerr << "failed to open file: " << path << std::endl;
    }
    return file;
}

void writeToFile(const std::string &filename, const std::string &content)
{
    std::ofstream file = openFileForWriting(filename);
    if (file.is_open())
    {
        file << content;
        file.close();
    }
}

std::string readFileToString(const std::string filename)
{
    // Read the entire file into the string using a string stream
    std::ostringstream ss;
    std::ifstream ifs(filename);

    if (!ifs.is_open())
    {
        std::cerr << "failed to open file: " << filename << std::endl;
    }

    ss << ifs.rdbuf();
    ifs.close();

    return ss.str();
}
