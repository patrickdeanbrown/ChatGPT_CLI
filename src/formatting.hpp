//  formatting.hpp
//
//

#ifndef formatting_hpp
#define formatting_hpp

#include <iostream>
#include <string>

/**
 * @brief Wraps and indents text output to a stream, preventing word breaks.
 *
 * Formats the input string so that no line exceeds the specified width,
 * wrapping at word boundaries and indenting each line as specified.
 *
 * @param input The text to be printed to the console.
 * @param width The maximum number of characters per line (excluding indent).
 * @param os The output stream to print to.
 * @param indent The number of spaces to add at the start of each printed line.
 */
void wrap(const std::string &input, size_t width, std::ostream &os, size_t indent);

#endif /* formatting_hpp */
