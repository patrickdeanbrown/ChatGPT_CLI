//  formatting.hpp
//
//

#ifndef formatting_hpp
#define formatting_hpp

#include <iostream>
#include <string>

/// @brief Wraps and indents text output to a stream preventing wrapping in the middle of words
///
/// @param input const std::string& the text to be printed to the console
/// @param width size_t the max number of characters to print on each line
/// @param os std::ostream& the output stream where the wrap prints input
/// @param indent size_t the number of spaces to add on each line printed
void wrap(std::string const &input, size_t width, std::ostream &os, size_t indent);

#endif /* formatting_hpp */
