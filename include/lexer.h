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
    struct Token* prev;
    struct Token* next;
} Token;

typedef struct {
    int size;
    Token* first;
    Token* last;
} TokenList;

/// @brief Lexes tokens from a line of code
/// @param line A string pointer pointing to a line of code
/// @param list The list of tokens to append tokens to
void lexer_scanTokens(const char* line, TokenList* list);

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

/// @brief Allocate memory for a new list of tokens
/// @return A pointer to a TokenList struct
TokenList* lexer_initTokenList();

/// @brief Allocate memory for a new token
/// @param val The char or c-string value of the token
/// @param type The token type
/// @return A pointer to a new token
Token* lexer_initToken(const char* val, TokenType type);

/// @brief Append new token to the end of the list
/// @param list The list to append the token to
/// @param val The char or c-string value of the token
/// @param type The token type
/// @return UTIL_SUCCESS or UTIL_FAILURE
int lexer_addToken(TokenList* list, char* val, TokenType type);

#endif
