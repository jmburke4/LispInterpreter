#include "lexer.h"

#ifndef TESTER_H
#define TESTER_H

#pragma GCC diagnostic ignored "-Wunused-parameter" // Suppress unused parameter warning
#pragma GCC diagnostic ignored "-Wunused-variable"  // Suppress unused variable warning
#pragma GCC diagnostic push

/// @brief Runs a series of print statements printing expect and actual results
/// @param _tokens A list of tokens to test with
void runTests(TokenList*);

void testEnvironment();

#pragma GCC diagnostic pop // Restore previous diagnostic settings

#endif
