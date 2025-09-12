#include "lexer.h"

#ifndef PARSER_H
#define PARSER_H

typedef enum { ATOM, CONS } SExprType;

typedef struct SExpression {
    SExprType type;
    union {
        char* atom; // for symbols, numbers, strings
        struct {
            struct SExpression* car;
            struct SExpression* cdr;
        } cons;
    };
} SExpression;

/// @brief Advances the linked list to the next token
void parser_advance();

/// @brief Returns the next token in the linked list but does not advance
/// @return The next token in the list
Token* parser_peek();

/// @brief Initializes the parser global variable with a list of tokens
/// @param head The head of the list of tokens to use
void parser_setList(Token* head);

SExpression* parser_parseList();
SExpression* parser_parseExpression();

void parser_print(SExpression* expr);
void parser_printQuote(SExpression* atom);

#endif
