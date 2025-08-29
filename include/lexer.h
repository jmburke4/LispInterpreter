#include <string.h>
#include "gll.h"

#ifndef LEXER_H
#define LEXER_H

#define MAX_WORD_LENGTH 12

typedef enum {
    L_IDENTIFIER,
    L_OPAREN,
    L_CPAREN,
    L_NUMBER,
    L_SQUOTE,
    L_DQUOTE,
} TokenType;

typedef struct {
    char* val;
    TokenType type;
} Token;

/// @brief Lexes tokens from a line of code
/// @param line A string pointer pointing to a line of code
void lexer_scanTokens(const char* line);

void lexer_lex(int current, const char* tokens, const char* line);

void lexer_lexNum(int current, const char* tokens, char* lexeme, const char* line);

void lexer_lexAlpha(int current, const char* tokens, char* lexeme, const char* line);

#endif
