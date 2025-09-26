#ifndef UTIL_C
#define UTIL_C

#define UTIL_SUCCESS 0
#define UTIL_FAILURE -1

#define UTIL_TRUE 1
#define UTIL_FALSE 0 

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m" // Resets to default color
// Usage: printf(ANSI_COLOR_RED "This text is red." ANSI_COLOR_RESET "\n");

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
