#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "lexer.h"

void lexer_scanTokens(const char* line, TokenList* list){
    lexer_lex(0, list, line);
}

void lexer_lex(int current, TokenList* tokens, const char* line){
    if (current <= (int)strlen(line)){
        char t = line[current];
        if (t == '('){
            lexer_addToken(tokens, "(", L_OPAREN);
            lexer_lex(current + 1, tokens, line);
        }
        else if (t == ')'){
            lexer_addToken(tokens, ")", L_CPAREN);
            lexer_lex(current + 1, tokens, line);
        }
        else if (t == '\''){
            lexer_addToken(tokens, "\'", L_SQUOTE);
            lexer_lex(current + 1, tokens, line);
        }
        else if (t == '\"'){
            lexer_addToken(tokens, "\"", L_DQUOTE);
            lexer_lex(current + 1, tokens, line);
        }
        else if (util_isNum(t)){
            char t_str[MAX_WORD_LENGTH];
            t_str[0] = t;
            t_str[1] = '\0';
            lexer_lexNum(current + 1, tokens, t_str, line);
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

void lexer_lexNum(int current, TokenList* tokens, char* lexeme, const char* line){
    if (current < (int)strlen(line)){
        char t = line[current];
        if (util_isNum(t)){
            char* t_str = &t;
            strncat(lexeme, t_str, 1);
            lexer_lexNum(current + 1, tokens, lexeme, line);
        }
        else {
            lexer_addToken(tokens, lexeme, L_NUMBER);
            lexer_lex(current, tokens, line);
        }
    }
}

void lexer_lexAlpha(int current, TokenList* tokens, char* lexeme, const char* line){
    if (current < (int)strlen(line)){
        char t = line[current];
        if (util_isAlpha(t)){
            char* t_str = &t;
            strncat(lexeme, t_str, 1);
            lexer_lexAlpha(current + 1, tokens, lexeme, line);
        }
        else {
            lexer_addToken(tokens, lexeme, L_IDENTIFIER);
            lexer_lex(current, tokens, line);
        }
    }
}

TokenList* lexer_initTokenList(){
    TokenList* list = (TokenList*)malloc(sizeof(TokenList));
    
    list->size = 0;
    list->first = NULL;
    list->last = NULL;
    
    return list;
}

Token* lexer_initToken(char* val, TokenType type){
    Token* node = (Token*)malloc(sizeof(Token));
    
    node->val = malloc(sizeof(char*) * strlen(val));
    strncpy(node->val, val, strlen(val));

    node->type = type;
    node->prev = NULL;
    node->next = NULL;
    
    return node;
}

int lexer_addToken(TokenList* list, char* val, TokenType type){
    Token* node = lexer_initToken(val, type);

    if (list->size == 0){
        list->first = node;
    }
    else {
        list->last->next = (struct Token*)node;
        node->prev = (struct Token*)list->last;
    }
    list->last = node;
    list->size++;

    return UTIL_SUCCESS;
}
