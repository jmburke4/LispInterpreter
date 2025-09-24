#include "lexer.h"

#ifndef UTIL_C
#define UTIL_C

#define UTIL_SUCCESS 0
#define UTIL_FAILURE -1

#define UTIL_TRUE 1
#define UTIL_FALSE 0 

/// @brief Prints a string to stdout
/// @param string The string to print
void util_printBuffer(const char *string);

/// @brief Checks if a char is a num
/// @param t The char to check
/// @return UTIL_TRUE or UTIL_FALSE
int util_isNum(char t);

/// @brief Checks if a char is a letter (case insensitive)
/// @param t The char to check
/// @return UTIL_TRUE or UTIL_FALSE
int util_isAlpha(char t);

/// @brief Checks if a char is a letter (case insensitive) or a number
/// @param t The char to check
/// @return UTIL_TRUE or UTIL_FALSE
int util_isAlphaNum(char t);

#endif
