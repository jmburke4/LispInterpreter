#include "lexer.h"

#ifndef UTIL_C
#define UTIL_C

#define UTIL_SUCCESS 0
#define UTIL_FAILURE -1

#define UTIL_TRUE 1
#define UTIL_FALSE 0 

/// @brief A type to represent a void function with a string pointer parameter 
typedef void (*callback_ptr)(const char*, TokenList*); 

/// @brief Reads contents of a file, and outputs each line to the passed callback function
/// @param filePath The filepath of the file to read
/// @param maxLineLength The maximum number of line characters to read
/// @param cb The callback function that takes a string pointer  
/// @return UTIL_SUCCESS or UTIL_FAILURE
int util_readFile(const char* filePath, int maxLineLength, TokenList* list, callback_ptr cb);

/// @brief Prints a string to stdout
/// @param string The string to print
void util_printBuffer(const char* string);

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
