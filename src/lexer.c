#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "lexer.h"

void lexer_scanTokens(const char *line, TokenList *list){ lexer_lex(0, list, line); }

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
            // char t_str[] = "\'\0";
            // if (line[current + 1] == '(') lexer_lexQuotedParen(current + 1, tokens, t_str, line);
            // else lexer_lexAlpha(current + 1, tokens, t_str, line);
            lexer_addToken(tokens, "\'\0", (TokenType)SINGLE_QUOTE);
            lexer_lex(current + 1, tokens, line);
        }
        else if (t == '.'){
            lexer_addToken(tokens, ".\0", (TokenType)DOT);
            lexer_lex(current + 1, tokens, line);
        }
        else if (t == '-'){
            lexer_addToken(tokens, "-\0", (TokenType)MINUS);
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
            // skip space
            lexer_lex(current + 1, tokens, line);
        }
        else if (t == '\r' || t == '\n' || t == ';'){
            // Exit on carriage return or new line or comment
        }
        else{
            fprintf(stderr, "ERROR LEXING CHAR: \'%c\'\n", t);
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
            char *t_str = &t;
            strncat(lexeme, t_str, 1);
            lexer_lexNum(current + 1, tokens, lexeme, line, 1);
        }
        else {
            if (hasDot == 1) lexer_addToken(tokens, lexeme, (TokenType)FLOAT);
            else lexer_addToken(tokens, lexeme, (TokenType)INT);
            lexer_lex(current, tokens, line);
        }
    }
}

void lexer_lexAlpha(int current, TokenList *tokens, char *lexeme, const char *line){
    if (current < (int)strlen(line)){
        char t = line[current];
        if (util_isAlphaNum(t)){
            char *t_str = &t;
            strncat(lexeme, t_str, 1);
            lexer_lexAlpha(current + 1, tokens, lexeme, line);
        }
        else {
            lexer_addToken(tokens, lexeme, (TokenType)STRING);
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
                lexer_lex(current + 1, tokens, line);
            }
        }
        else if (t == '('){
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

void lexer_printTokens(TokenList *tokens){
    Token *head = (Token*)tokens->first;
    while (head != NULL){
        fprintf(stdout, "TYPE: %02d TOKEN: %s\n", head->type, head->val);
        fflush(stdout);
        head = (Token*)head->next;
    }
    //fprintf(stdout, "Lexed %d tokens.\n", tokens->size);
}

TokenList *lexer_initTokenList(){
    TokenList *list = (TokenList*)malloc(sizeof(TokenList));
    
    list->size = 0;
    list->first = NULL;
    list->last = NULL;
    
    return list;
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

    return UTIL_SUCCESS;
}

void lexer_clearTokenList(TokenList *list){
    Token *iterator = list->first;
    Token *tmp = NULL;
    while (iterator != NULL){
        tmp = iterator;
        iterator = (Token*)iterator->next;
        free(tmp);
        list->size--;
    }
}
