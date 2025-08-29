#include <stdio.h>
#include <string.h>
#include "util.h"
#include "lexer.h"

void lexer_scanTokens(const char* line){
    lexer_lex(0, "NOT_IMPLEMENTED", line);

    fprintf(stdout, "EOL\n");
    // add tokens to master token tree
}

void lexer_lex(int current, const char* tokens, const char* line){
    if (current <= (int)strlen(line)){
        char t = line[current];
        if (t == '('){
            fprintf(stdout, "\tAdd L_OPAREN\n");

            // single char
            lexer_lex(current + 1, tokens, line);
        }
        else if (t == ')'){
            fprintf(stdout, "\tAdd L_CPAREN\n");

            // single char
            lexer_lex(current + 1, tokens, line);
        }
        else if (t == '\''){
            fprintf(stdout, "\tAdd L_SQUOTE\n");

            // single char
            lexer_lex(current + 1, tokens, line);
        }
        else if (t == '\"'){
            fprintf(stdout, "\tAdd L_DQUOTE\n");

            // single char
            lexer_lex(current + 1, tokens, line);
        }
        else if (util_isNum(t)){
            // multi char
            char t_str[MAX_WORD_LENGTH];
            t_str[0] = t;
            t_str[1] = '\0';
            lexer_lexNum(current + 1, tokens, t_str, line);
        }
        else if (util_isAlpha(t)){
            // multi char
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
            fprintf(stderr, "DEFAULT: \'%c\'\n", t);
        }
    }
}

void lexer_lexNum(int current, const char* tokens, char* lexeme, const char* line){
    if (current < (int)strlen(line)){
        char t = line[current];
        if (util_isNum(t)){
            char* t_str = &t;
            strncat(lexeme, t_str, 1);
            lexer_lexNum(current + 1, tokens, lexeme, line);
        }
        else {
            fprintf(stdout, "\tAdd %s\n", lexeme);
            lexer_lex(current, tokens, line);
        }
    }
}

void lexer_lexAlpha(int current, const char* tokens, char* lexeme, const char* line){
    if (current < (int)strlen(line)){
        char t = line[current];
        if (util_isAlpha(t)){
            char* t_str = &t;
            strncat(lexeme, t_str, 1);
            lexer_lexAlpha(current + 1, tokens, lexeme, line);
        }
        else {
            fprintf(stdout, "\tAdd %s\n", lexeme);
            lexer_lex(current, tokens, line);
        }
    }
}
