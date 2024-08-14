//
//  formatting.cpp
//  chatgpt_cli
//
//  Created by Patrick Brown on 8/13/23.
//

#include "formatting.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void wrap(std::string const &input, size_t width, std::ostream &os, size_t defaultIndent = 0)
{
    std::istringstream ss(input);
    std::string line;

    // Iterate through the lines of the input
    while (std::getline(ss, line))
    {
        // If the line is empty or only consists of whitespace, print as is.
        if (line.find_first_not_of(' ') == std::string::npos)
        {
            os << line << '\n';
            continue;
        }

        // Check for preceding whitespace
        size_t originalIndent = line.find_first_not_of(' ');
        size_t totalIndent = originalIndent + defaultIndent;

        // Remove originalIndent from the line before wrapping
        line = line.substr(originalIndent);

        // Tokenize line into words
        std::vector<std::string> words;
        std::istringstream lineStream(line);
        std::string word;

        while (lineStream >> word)
        {
            words.push_back(word);
        }

        // Construct new lines based on the specified width
        std::string newLine = std::string(totalIndent, ' ');
        for (const auto &w : words)
        {
            if (newLine.length() + w.length() > width + totalIndent)
            {
                os << newLine << '\n';
                newLine = std::string(totalIndent, ' ');
            }
            if (newLine.length() > totalIndent)
                newLine += ' ';
            newLine += w;
        }
        os << newLine << '\n';
    }
}
