#ifndef LEXER_H
#define LEXER_H

#define MAX_WORD_LENGTH 12

typedef enum {
    OPEN_PAREN, CLOSE_PAREN,
    
    MINUS, PLUS, SLASH, STAR,
    
    SINGLE_QUOTE, DOT, NIL,
    
    NOT, NOTEQ,
    EQ, EQEQ,
    GT, GTE,
    LT, LTE,

    STRING, INT, FLOAT
} TokenType;

typedef struct {
    char *val;
    TokenType type;
    struct Token *prev;
    struct Token *next;
} Token;

typedef struct {
    int size;
    int oparen;
    int cparen;
    Token *first;
    Token *last;
} TokenList;

/// @brief Append new token to the end of the list
/// @param list The list to append the token to
/// @param val The char or c-string value of the token
/// @param type The token type
/// @return UTIL_SUCCESS or UTIL_FAILURE
int lexer_addToken(TokenList *list, char *val, TokenType type);

/// @brief Frees the tokens in a TokenList and resets the token counter
/// @param list The TokenList to clear
void lexer_clearTokenList(TokenList *list);

/// @brief Allocate memory for a new token
/// @param val The char or c-string value of the token
/// @param type The token type
/// @return A pointer to a new token
Token *lexer_initToken(char *val, TokenType type);

/// @brief Allocate memory for a new list of tokens
/// @return A pointer to a TokenList struct
TokenList *lexer_initTokenList();

/// @brief The recursive function to process each character
/// @param current The current index within the line being scanned
/// @param tokens The list of tokens
/// @param line The line to scan
void lexer_lex(int current, TokenList *tokens, const char *line);

/// @brief The recursive function to process multi-char strings
/// @param current The current index within the line being scanned
/// @param tokens The list of tokens
/// @param lexeme The multi-char string being scanned
/// @param line The line to scan
void lexer_lexAlpha(int current, TokenList *tokens, char *lexeme, const char *line);

/// @brief The recursive function to process multi-char numbers
/// @param current The current index within the line being scanned
/// @param tokens The list of tokens
/// @param lexeme The multi-char number being scanned
/// @param line The line to scan
/// @param hasDot Flag that is set to determine whether the lexeme is a float or an integer
void lexer_lexNum(int current, TokenList *tokens, char *lexeme, const char *line, int hasDot);

/// @brief The recursive function to distribute a quote across atoms in parentheses
/// @param current The current index within the line being scanned
/// @param tokens The list of tokens to append to
/// @param lexeme The multi-char string starting with a quote to be scanned
/// @param line The line to scan
void lexer_lexQuotedParen(int current, TokenList *tokens, char *lexeme, const char *line);

/// @brief Adds in explicit opening and close parentheses to the token list
/// @param list A pointer to the TokenList to add parentheses to
void lexer_normalizeList(TokenList *list);

/// @brief Prints each token in a TokenList
/// @param tokens A TokenList struct with a pointer to the first token
void lexer_printTokens(TokenList *tokens);

/// @brief Lexes tokens from a line of code
/// @param line A string pointer pointing to a line of code
/// @param list The list of tokens to append tokens to
void lexer_scanTokens(const char *line, TokenList *list);

#endif
