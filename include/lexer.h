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

/// @brief The recursive function to process each character
/// @param current The current index within the line being scanned
/// @param tokens The list of tokens
/// @param line The line to scan
void lexer_lex(int current, const char* tokens, const char* line);

/// @brief The recursive function to process multi-char numbers
/// @param current The current index within the line being scanned
/// @param tokens The list of tokens
/// @param lexeme The multi-char number being scanned
/// @param line The line to scan
void lexer_lexNum(int current, const char* tokens, char* lexeme, const char* line);

/// @brief The recursive function to process multi-char strings
/// @param current The current index within the line being scanned
/// @param tokens The list of tokens
/// @param lexeme The multi-char string being scanned
/// @param line The line to scan
void lexer_lexAlpha(int current, const char* tokens, char* lexeme, const char* line);

#endif
