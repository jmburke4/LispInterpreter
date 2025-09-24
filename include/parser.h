#include "lexer.h"

#ifndef PARSER_H
#define PARSER_H

typedef enum { ATOM, CONS } SExprType;

typedef struct SExpression {
    SExprType type;
    union {
        char *atom; // for symbols, numbers, strings
        struct {
            struct SExpression *car;
            struct SExpression *cdr;
        } cons;
    };
} SExpression;

/// @brief Advances the linked list to the next token
void parser_advance();

/// @brief Returns the next token in the linked list but does not advance
/// @return The next token in the list
Token *parser_peek();

/// @brief Initializes the parser global variable with a list of tokens
/// @param head The head of the list of tokens to use
void parser_setList(Token *head);

/// @brief Parses a nested list of S-Expressions
/// @return An S-Expression
SExpression *parser_parseList();

/// @brief Parses an S-Expression
/// @return An S-Expression
SExpression *parser_parseExpression();

/// @brief Prints an S-Expression
/// @param expr The S-Expression to print
void parser_print(SExpression *expr);

/// @brief Recursively frees the atoms in an S-Expression
/// @param expr The S-Expression to free
void parser_clearExpression(SExpression *expr);

#endif
