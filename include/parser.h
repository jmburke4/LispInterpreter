#include "lexer.h"
#include "sexpr.h"

#ifndef PARSER_H
#define PARSER_H

/// @brief Advances the linked list to the next token
void parser_advance();

/// @brief Recursively frees the atoms in an ```SExpression```
/// @param expr The ```SExpression``` to free
void parser_clearExpression(SExpression *expr);

/// @brief Parses an ```SExpression```
/// @return An ```SExpression```
SExpression *parser_parseExpression();

/// @brief Parses a nested list of ```SExpression```s
/// @return An ```SExpression```
SExpression *parser_parseList();

/// @brief Initializes the parser global variable with a list of tokens
/// @param head The head of the list of tokens to use
void parser_setList(Token *head);

#endif
