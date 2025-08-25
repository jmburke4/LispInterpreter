#ifndef UTIL_C
#define UTIL_C

/// @brief A type to represent a void function with a string pointer parameter 
typedef void (*callback_ptr)(const char*); 

/// @brief Reads contents of a file, and outputs each line to the passed callback function
/// @param filePath The filepath of the file to read
/// @param maxLineLength The maximum number of line characters to read
/// @param cb The callback function that takes a string pointer
/// @return 0 for success, -1 for error
int util_readFile(const char* filePath, int maxLineLength, callback_ptr cb);

/// @brief Prints a string to stdout
/// @param string The string to print
void util_printBuffer(const char* string);

#endif
