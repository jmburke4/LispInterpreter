#include "lexer.h"
#include "sexpr.h"

#ifndef PARSER_H
#define PARSER_H

/// @brief Advances the linked list to the next token
void parser_advance();

/// @brief Recursively frees the atoms in an S-Expression
/// @param expr The S-Expression to free
void parser_clearExpression(SExpression *expr);

/// @brief Parses an S-Expression
/// @return An S-Expression
SExpression *parser_parseExpression();

/// @brief Parses a nested list of S-Expressions
/// @return An S-Expression
SExpression *parser_parseList();

/// @brief Initializes the parser global variable with a list of tokens
/// @param head The head of the list of tokens to use
void parser_setList(Token *head);

#endif
