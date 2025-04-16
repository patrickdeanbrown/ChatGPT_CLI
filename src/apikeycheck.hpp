// apikeycheck.hpp
//
// Checks validity of the OpenAI API key at program startup.
#ifndef APIKEYCHECK_HPP
#define APIKEYCHECK_HPP

/// Checks if the OpenAI API key is valid by making a minimal request to OpenAI's API.
/// If the key is invalid or inactive, prints an error and exits the program.
void checkOpenAIKeyOrExit();

#endif // APIKEYCHECK_HPP
