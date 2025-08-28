#include <stdio.h>
#include <string.h>
#include "util.h"
#include "lexer.h"

void lexer_scanTokens(const char* line){
    //gll_t* tokens = gll_init();

    lexer_lex(0, "placeholder", line);

    printf("EOL\n");
}

void lexer_lex(int current, const char* tokens, const char* line){
    if (current <= (int)strlen(line)){
        char t = line[current];
        if (t == '('){
            fprintf(stdout, "Add L_OPAREN\n");

            // single char
            lexer_lex(current + 1, tokens, line);
        }
        else if (t == ')'){
            fprintf(stdout, "Add L_CPAREN\n");

            // single char
            lexer_lex(current + 1, tokens, line);
        }
        else if (t == '\''){
            fprintf(stdout, "Add L_SQUOTE\n");

            // single char
            lexer_lex(current + 1, tokens, line);
        }
        else if (t == '\"'){
            fprintf(stdout, "Add L_DQUOTE\n");

            // single char
            lexer_lex(current + 1, tokens, line);
        }
        else if (util_isNum(t)){
            //fprintf(stdout, "Add L_NUM\n");

            // multi char
            char* t_str = &t;
            lexer_lexNum(current + 1, t, line);
        }
        else if (util_isAlpha(t)){
            fprintf(stdout, "Add L_ALPHA\n");

            // multi char
        }
        else if (t == ' '){
            // skip space
            lexer_lex(current + 1, tokens, line);
        }
        else{
            fprintf(stderr, "DEFAULT: \'%c\'\n", t);
        }
    }
    else {
        // Reached end of the line
        return;
    }
}

void lexer_lexNum(int current, char* lexeme, const char* line){
    if (current < (int)strlen(line)){
        char t = line[current];
        if (util_isNum(t)){
            fprintf("\tlexeme: %s\n", lexeme);
            lexer_lexNum(current + 1, strncat(lexeme, t, 1), line);
        }
        else {
            fprintf(stdout, "ADD %s\n", lexeme);
        }
    }
}
