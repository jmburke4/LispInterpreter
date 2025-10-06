#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "util.h"
#include "lexer.h"

int lexer_addToken(TokenList *list, char *val, TokenType type){
    Token *node = lexer_initToken(val, type);

    if (list->size == 0){
        list->first = node;
    }
    else {
        if (list->last->next == NULL){
            list->last->next = (struct Token*)node;
            node->prev = (struct Token*)list->last;
        }
        else {
            printf("ERROR: Next pointer of last node in list is not null\n");
        }
    }
    list->last = node;
    list->size++;

    if (node->type == (TokenType)OPEN_PAREN) list->oparen++;
    if (node->type == (TokenType)CLOSE_PAREN) list->cparen++;

    return UTIL_SUCCESS;
}

void lexer_clearTokenList(TokenList *list){
    Token *iterator = list->first;
    Token *tmp = NULL;
    while (iterator != NULL){
        if (iterator->type == (TokenType)OPEN_PAREN) list->oparen--;
        if (iterator->type == (TokenType)CLOSE_PAREN) list->cparen--;
        
        tmp = iterator;
        iterator = (Token*)iterator->next;
        free(tmp);
        list->size--;
    }
}

Token *lexer_initToken(char *val, TokenType type){
    Token *node = (Token*)malloc(sizeof(Token));
    
    node->val = malloc(sizeof(char*) * strlen(val));
    strncpy(node->val, val, strlen(val) + 1);

    node->type = type;
    node->prev = NULL;
    node->next = NULL;
    
    return node;
}

TokenList *lexer_initTokenList(){
    TokenList *list = (TokenList*)malloc(sizeof(TokenList));
    list->size = 0;
    list->oparen = 0;
    list->cparen = 0;
    list->first = NULL;
    list->last = NULL;
    return list;
}

void lexer_lex(int current, TokenList *tokens, const char *line){
    if (current < (int)strlen(line)){
        char t = line[current];
        if (t == '('){
            lexer_addToken(tokens, "(\0", (TokenType)OPEN_PAREN);
            lexer_lex(current + 1, tokens, line);
        }
        else if (t == ')'){
            lexer_addToken(tokens, ")\0", (TokenType)CLOSE_PAREN);
            lexer_lex(current + 1, tokens, line);
        }
        else if (t == '\''){
            char t_str[] = "\'\0";
            if (line[current + 1] == '(') lexer_lexQuotedParen(current + 1, tokens, t_str, line);
            else lexer_lexAlpha(current + 1, tokens, t_str, line);
        }
        else if (t == '\"'){
            // Lex strings like "Hello"
            // The quotes are part of the string value
            char t_str[MAX_WORD_LENGTH];
            t_str[0] = t;
            t_str[1] = '\0';
            lexer_lexString(current + 1, tokens, t_str, line);
        }
        else if (t == '.'){
            lexer_addToken(tokens, ".\0", (TokenType)DOT);
            lexer_lex(current + 1, tokens, line);
        }
        else if (t == '-'){
            if (line[current + 1] == ' '){
                // To indicate subtraction
                lexer_addToken(tokens, "-\0", (TokenType)MINUS);
                lexer_lex(current + 1, tokens, line);
            } 
            else {
                // To indicate a negative number
                char t_str[MAX_WORD_LENGTH];
                t_str[0] = t;
                t_str[1] = '\0';
                lexer_lexNum(current + 1, tokens, t_str, line, 0);
            }
        }
        else if (t == '+'){
            lexer_addToken(tokens, "+\0", (TokenType)PLUS);
            lexer_lex(current + 1, tokens, line);
        }
        else if (t == '*'){
            lexer_addToken(tokens, "*\0", (TokenType)STAR);
            lexer_lex(current + 1, tokens, line);
        }
        else if (t == '/'){
            lexer_addToken(tokens, "/\0", (TokenType)SLASH);
            lexer_lex(current + 1, tokens, line);
        }
        else if (t == '%'){
            lexer_addToken(tokens, "%%\0", (TokenType)MOD);
            lexer_lex(current + 1, tokens, line);
        }
        else if (util_isNum(t)){
            char t_str[MAX_WORD_LENGTH];
            t_str[0] = t;
            t_str[1] = '\0';
            lexer_lexNum(current + 1, tokens, t_str, line, 0);
        }
        else if (util_isAlpha(t)){
            char t_str[MAX_WORD_LENGTH];
            t_str[0] = t;
            t_str[1] = '\0';
            lexer_lexAlpha(current + 1, tokens, t_str, line);
        }
        else if (t == ' '){
            // skip spaces
            lexer_lex(current + 1, tokens, line);
        }
        else if (t == '\r' || t == '\n' || t == ';' || t == 7){
            // Exit on carriage return or new line or comment
        }
        else{
            fprintf(stderr, "ERROR LEXING CHAR: %c (%d)\n", t, t);
        }
    }
}

void lexer_lexAlpha(int current, TokenList *tokens, char *lexeme, const char *line){
    // Lex alphabetical characters for identifiers or strings
    if (current < (int)strlen(line)){
        char t = line[current];
        if (util_isAlphaNum(t)){
            char *t_str = &t;
            strncat(lexeme, t_str, 1);
            lexer_lexAlpha(current + 1, tokens, lexeme, line);
        }
        else {
            TokenType type = STRING;
            if (lexeme[0] == '\'') type = SINGLE_QUOTE;
            else if (strcmp(lexeme, "eq") == 0) type = EQ;
            else if (strcmp(lexeme, "neq") == 0) type = NOTEQ;
            else if (strcmp(lexeme, "lt") == 0) type = LT;
            else if (strcmp(lexeme, "lte") == 0) type = LTE;
            else if (strcmp(lexeme, "gt") == 0) type = GT;
            else if (strcmp(lexeme, "gte") == 0) type = GTE;
            
            lexer_addToken(tokens, lexeme, type);
            lexer_lex(current, tokens, line);
        }
    }
}

void lexer_lexNum(int current, TokenList *tokens, char *lexeme, const char *line, int hasDot){
    if (current < (int)strlen(line)){
        char t = line[current];
        if (util_isNum(t)){
            char *t_str = &t;
            strncat(lexeme, t_str, 1);
            lexer_lexNum(current + 1, tokens, lexeme, line, hasDot);
        }
        else if (t == '.'){
            // For lexing decimals
            char *t_str = &t;
            strncat(lexeme, t_str, 1);
            // Set the hasDot flag to determine the token type
            lexer_lexNum(current + 1, tokens, lexeme, line, 1);
        }
        else {
            if (hasDot == 1) lexer_addToken(tokens, lexeme, (TokenType)FLOAT);
            else lexer_addToken(tokens, lexeme, (TokenType)INT);
            lexer_lex(current, tokens, line);
        }
    }
}

void lexer_lexQuotedParen(int current, TokenList *tokens, char *lexeme, const char *line){
    if (current < (int)strlen(line)){
        char t = line[current];
        if (t == ')'){
            if (line[current - 1] == '('){ // Need error handling for this index access
                lexer_addToken(tokens, "\'()\0", (TokenType)SINGLE_QUOTE);
                lexer_lex(current + 1, tokens, line);
            }
            else {
                lexer_addToken(tokens, lexeme, (TokenType)SINGLE_QUOTE);
                lexer_addToken(tokens, ")\0", (TokenType)CLOSE_PAREN);
                lexer_lex(current + 1, tokens, line);
            }
        }
        else if (t == '('){
            lexer_addToken(tokens, "(\0", (TokenType)OPEN_PAREN);
            lexer_lexQuotedParen(current + 1, tokens, lexeme, line);
        }
        else if (t == ' '){
            // Distribute the quote across parentheses ex. '(a b) -> 'a 'b
            lexer_addToken(tokens, lexeme, (TokenType)SINGLE_QUOTE);
            char t_str[] = "\'\0";
            lexer_lexQuotedParen(current + 1, tokens, t_str, line);
        }
        else {
            char *t_str = &t;
            strncat(lexeme, t_str, 1);
            lexer_lexQuotedParen(current + 1, tokens, lexeme, line);
        }
    }
}

void lexer_lexString(int current, TokenList *tokens, char *lexeme, const char *line){
    if (current < (int)strlen(line)){
        char t = line[current];
        char *t_str = &t;
        strncat(lexeme, t_str, 1);
        if (t == '\"'){
            lexer_addToken(tokens, lexeme, DOUBLE_QUOTE);
            lexer_lex(current, tokens, line);
        }
        if (strlen(lexeme) == (MAX_WORD_LENGTH - 1)){
            fprintf(stderr, "String that begins with %s cannot be greater than %d characters\n.", lexeme, MAX_WORD_LENGTH);
            return;
        }
        lexer_lexString(current + 1, tokens, lexeme, line);
    }
}

void lexer_printTokens(TokenList *tokens){
    Token *head = (Token*)tokens->first;
    while (head != NULL){
        fprintf(stdout, "TYPE: %02d TOKEN: %s\n", head->type, head->val);
        fflush(stdout);
        head = (Token*)head->next;
    }
    fprintf(stdout, "Lexed %d tokens (%d OPEN_PAREN, %d CLOSE_PAREN).\n", tokens->size, tokens->oparen, tokens->cparen);
}

void lexer_scanTokens(const char *line, TokenList *list){ lexer_lex(0, list, line); }
