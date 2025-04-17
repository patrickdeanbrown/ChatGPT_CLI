// apikeycheck.hpp
//
// Checks validity of the OpenAI API key at program startup.
#ifndef APIKEYCHECK_HPP
#define APIKEYCHECK_HPP

/**
 * @brief Checks the validity of the OpenAI API key at program startup.
 *
 * Makes a minimal request to the OpenAI API to verify the key.
 * If the key is missing, invalid, or inactive, prints an error message and terminates the program.
 * This function does not return if the key is not valid.
 *
 * @note This function should be called before any other OpenAI API operations.
 */
void checkOpenAIKeyOrExit();

#endif // APIKEYCHECK_HPP
