//  commandcontext.hpp
//
// CommandContext holds information about the user command and its arguments.

#ifndef commandcontext_hpp
#define commandcontext_hpp

#include <string>
#include <vector>

/// @class CommandContext
/// @brief Container for commands read in from input, in the form of "%command [arg1 arg2]"
/// Separates the raw command into more easily managed and accessible components of a
/// command and its arguments.
class CommandContext
{
  public:
    /**
     * @brief Parses a raw command string and separates it into the command and its arguments.
     * @param rawCommandInput The raw input string in the form "%command [arg1 arg2]".
     */
    void setCommandAndArgs(const std::string& rawCommandInput);

    /**
     * @brief Returns the parsed command string.
     * @return The command extracted from the raw input.
     */
    std::string getCommand() const;

    /**
     * @brief Returns the argument at the specified index.
     * @param argumentIndex The index of the argument to return.
     * @return The argument at the specified index.
     * @throws std::out_of_range if the index is invalid.
     */
    std::string getArgument(size_t argumentIndex) const;
    
    /**
     * @brief Returns the number of parsed arguments.
     * @return The number of arguments.
     */
    size_t getArgumentsSize() const;

  private:
    std::string m_command;
    std::vector<std::string> m_arguments;

    /**
     * @brief Parses a raw string containing a command keyword and arguments and updates member variables.
     * @param rawCommandInput The raw string in the form "%command arg1 arg2 arg3".
     */
    void _parseCommand(const std::string& rawCommandInput);
};

#endif /* commandcontext_hpp */
