#ifndef UTIL_C
#define UTIL_C

/// @brief Checks if a char is a letter (case insensitive)
/// @param t The char to check
/// @return UTIL_TRUE or UTIL_FALSE
int util_isAlpha(char t);

/// @brief Checks if a char is a letter (case insensitive) or a number
/// @param t The char to check
/// @return UTIL_TRUE or UTIL_FALSE
int util_isAlphaNum(char t);

/// @brief Checks if a char is a num
/// @param t The char to check
/// @return UTIL_TRUE or UTIL_FALSE
int util_isNum(char t);

/// @brief Prints a string to stdout
/// @param string The string to print
void util_printBuffer(const char *string);

#endif
