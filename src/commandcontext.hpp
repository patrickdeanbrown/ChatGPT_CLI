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
    /// @brief Member function of ComandContext. Parses a string in the form
    /// of "%command [arg1 arg2]" and separates the command and arguments.
    /// Overwrites the member variables m_command and m_arguments.
    ///
    /// @param rawCommandInput std::string expected in the form of
    /// "%command [arg1 arg2]"
    void setCommandAndArgs(const std::string& rawCommandInput);

    /// @brief Member function of CommandContext. Getter for m_command.
    ///
    /// @return m_command std::string
    std::string getCommand() const;

    /// @brief Member function of CommandContext. Getter for m_arguments.
    /// @param argumentIndex size_t the index of the argument to return.
    /// @return argument at a specified index std::string
    std::string getArgument(size_t argumentIndex) const;
    
    /// @brief Member function of CommandContext. Getter for the size of m_arguments
    /// @return size_t the size of m_arguments
    size_t getArgumentsSize() const;

  private:
    std::string m_command;
    std::vector<std::string> m_arguments;

    /// @brief CommandContext member function. Parses a raw string containing a command keyword and arguments
    /// in the form of "%command arg1 arg2 arg3". It changes the member variables command and arguments
    ///
    /// @param rawCommandInput std::string in the form of "%command arg1 arg2 arg3"
    void _parseCommand(const std::string& rawCommandInput);
};

#endif /* commandcontext_hpp */
