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
        else if (t == '.'){
            lexer_addToken(tokens, ".\0", (TokenType)DOT);
            lexer_lex(current + 1, tokens, line);
        }
        else if (t == '-'){
            if (line[current + 1] == ' '){
                lexer_addToken(tokens, "-\0", (TokenType)MINUS);
                lexer_lex(current + 1, tokens, line);
            } 
            else {
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

void lexer_lexAlpha(int current, TokenList *tokens, char *lexeme, const char *line){
    if (current < (int)strlen(line)){
        char t = line[current];
        if (util_isAlphaNum(t)){
            char *t_str = &t;
            strncat(lexeme, t_str, 1);
            lexer_lexAlpha(current + 1, tokens, lexeme, line);
        }
        else {
            if (lexeme[0] == '\'') lexer_addToken(tokens, lexeme, (TokenType)SINGLE_QUOTE);
            else lexer_addToken(tokens, lexeme, (TokenType)STRING);
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

void lexer_normalizeList(TokenList *list){
    // This function will convert (a b c) -> (a (b c))
    // If you have a function call with parameters, you must use explicit parentheses
    //      ex. (quote a b) will be normalized to (quote (a b)) // which is WRONG
    //          You must do ((quote a) b) -> ((quote a) b)

    int nonParenTokens = list->size - list->oparen - list->cparen;
    if (list->oparen != list->cparen) {
        fprintf(stderr, "Mismatching number of parentheses: %d OPEN, %d CLOSE. Aborting...\n\n", list->oparen, list->cparen);
        return;
    }
    else if ((nonParenTokens - 1) == list->oparen){
        // fprintf(stdout, "List already normalized.\n");
    }
    else {
        int missingPairs = (nonParenTokens - 1) - list->oparen;
        // printf("Missing %d sets of parentheses.\n", missingPairs);
        Token* iter = list->first;
        int count = 0;

        while (iter != NULL && missingPairs > 0){
            if (iter->type != (TokenType)OPEN_PAREN && iter->type != (TokenType)CLOSE_PAREN){
                Token* nxt = (Token*)iter->next;
                if (nxt->type != (TokenType)CLOSE_PAREN) count++;
                if (count == 2){
                    // add parentheses
                    Token* newO = lexer_initToken("(\0", (TokenType)OPEN_PAREN);
                    Token* newC = lexer_initToken(")\0", (TokenType)CLOSE_PAREN);
                    
                    // Insert opening parentheses before current token
                    Token* prev = (Token*)iter->prev;
                    prev->next = (struct Token*)newO;
                    newO->prev = iter->prev;
                    iter->prev = (struct Token*)newO;
                    newO->next = (struct Token*)iter;

                    // Add closing parentheses to the end of the list
                    newC->prev = (struct Token*)list->last;
                    list->last->next = (struct Token*)newC;
                    list->last = newC;

                    list->size += 2;
                    list->oparen++;
                    list->cparen++;

                    count--;
                }
            }
            iter = (Token*)iter->next;
            missingPairs = (nonParenTokens - 1) - list->oparen;
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
    fprintf(stdout, "Lexed %d tokens (%d OPEN_PAREN, %d CLOSE_PAREN).\n", tokens->size, tokens->oparen, tokens->cparen);
}

void lexer_scanTokens(const char *line, TokenList *list){ lexer_lex(0, list, line); }
