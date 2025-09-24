#ifndef LEXER_H
#define LEXER_H

#define MAX_WORD_LENGTH 12

// Copied enums from https://craftinginterpreters.com/scanning.html#:~:text=lox%3B%0A%0Aenum-,TokenType,-%7B%0A%20%20//%20Single%2Dcharacter
typedef enum {
  TATOM,
  
  // Single-character tokens.
  OPEN_PAREN, CLOSE_PAREN, OPEN_BRACE, CLOSE_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
  SINGLE_QUOTE, DOUBLE_QUOTE,

  // One or two character tokens.
  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  // Literals.
  IDENTIFIER, STRING, NUMBER,

  // Keywords.
  AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

  LEXER_EOF
} TokenType;

typedef struct {
  char *val;
  TokenType type;
  struct Token *prev;
  struct Token *next;
} Token;

typedef struct {
  int size;
  Token *first;
  Token *last;
} TokenList;

/// @brief Lexes tokens from a line of code
/// @param line A string pointer pointing to a line of code
/// @param list The list of tokens to append tokens to
void lexer_scanTokens(const char *line, TokenList *list);

/// @brief The recursive function to process each character
/// @param current The current index within the line being scanned
/// @param tokens The list of tokens
/// @param line The line to scan
void lexer_lex(int current, TokenList *tokens, const char *line);

/// @brief The recursive function to process multi-char numbers
/// @param current The current index within the line being scanned
/// @param tokens The list of tokens
/// @param lexeme The multi-char number being scanned
/// @param line The line to scan
void lexer_lexNum(int current, TokenList *tokens, char *lexeme, const char *line);

/// @brief The recursive function to process multi-char strings
/// @param current The current index within the line being scanned
/// @param tokens The list of tokens
/// @param lexeme The multi-char string being scanned
/// @param line The line to scan
void lexer_lexAlpha(int current, TokenList *tokens, char *lexeme, const char *line);

/// @brief The recursive function to distribute a quote across atoms in parentheses
/// @param current The current index within the line being scanned
/// @param tokens The list of tokens to append to
/// @param lexeme The multi-char string starting with a quote to be scanned
/// @param line The line to scan
void lexer_lexQuotedParen(int current, TokenList *tokens, char *lexeme, const char *line);

/// @brief Prints each token in a TokenList
/// @param tokens A TokenList struct with a pointer to the first token
void lexer_printTokens(TokenList *tokens);

/// @brief Allocate memory for a new list of tokens
/// @return A pointer to a TokenList struct
TokenList *lexer_initTokenList();

/// @brief Allocate memory for a new token
/// @param val The char or c-string value of the token
/// @param type The token type
/// @return A pointer to a new token
Token *lexer_initToken(char *val, TokenType type);

/// @brief Append new token to the end of the list
/// @param list The list to append the token to
/// @param val The char or c-string value of the token
/// @param type The token type
/// @return UTIL_SUCCESS or UTIL_FAILURE
int lexer_addToken(TokenList *list, char *val, TokenType type);

/// @brief Frees the tokens in a TokenList and resets the token counter
/// @param list The TokenList to clear
void lexer_clearTokenList(TokenList *list);

#endif
