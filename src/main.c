#include <stdio.h>
#include <string.h>

#include "util.h"
#include "lexer.h"
#include "sexpr.h"
#include "parser.h"
#include "../include/parser.h" // This is here for intellisense
#include "tester.h"

#define LINE_BUFFER_SIZE 256

void runLine(char[], TokenList*, int);

int main(int argc, char *argv[]) {
    int result = 0;
    TokenList *tokens = lexer_initTokenList();
    char buffer[LINE_BUFFER_SIZE];

    if (argc == 2 && strcmp(argv[1], "test") != 0){
        FILE *fptr = fopen((char*)argv[1], "r");
        if (fptr == NULL) {
            fprintf(stderr, "Error for filepath: \'%s\'\n", (char*)argv[1]);
            return UTIL_FAILURE;
        }

        while (fgets(buffer, sizeof(buffer), fptr) != NULL){
            runLine(buffer, tokens, 0);
        }

        if (!feof(fptr)) perror("Error reading file");
        if (fclose(fptr) != 0) perror("Error closing file");
    }
    else if (argc == 2 && strcmp(argv[1], "test") == 0) testEnvironment(); //runTests(tokens);
    else {
        printf("Welcome to the Lisp Interpreter REPL!\nUse Ctrl+C to exit\n");
        
        while (1){
            printf("\n>");

            if (fgets(buffer, sizeof(buffer), stdin) != NULL){
                runLine(buffer, tokens, 1);
            } 
            else {
                fprintf(stderr, "Error reading input.\n");
            }
        }
    }

    return result;
}

void runLine(char _buffer[], TokenList* _tokens, int _repl){
    // fgets includes the newline character if there's space.
    // To remove it, you can find and replace it with a null terminator.
    size_t len = strlen(_buffer);
    if (len > 0 && _buffer[len-1] == '\n') {
        _buffer[len-1] = '\0';
    }
    
    lexer_scanTokens(_buffer, _tokens);
    if (_tokens->size > 0){
        if (_repl == 0) printf("\n>%s\n", _buffer);
        
        lexer_normalizeList(_tokens);
        parser_setList(_tokens->first);
        SExpression *exp = parser_parseExpression();
        eval(exp);
        lexer_clearTokenList(_tokens);
        print(exp);
        exp = parser_clearExpression(exp);
        
        // Flush output stream for debugging
        printf("\n");
        fflush(stdout);
    }
}
