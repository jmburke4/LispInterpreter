#include <stdio.h>
#include <string.h>
#include "util.h"
#include "lexer.h"
#include "parser.h"
#include "../include/parser.h" // This is here for intellisense

#define LINE_BUFFER_SIZE 256

int main(int argc, char* argv[]) {
    int result = 0;
    TokenList* tokens = lexer_initTokenList();
    
    if (argc == 2){
        // Run filename passed by command line (ex. "./bin/tests/c1.txt")
        result = util_readFile((char*)argv[1], LINE_BUFFER_SIZE, tokens, lexer_scanTokens);
        
        parser_setList(tokens->first);
        SExpression* exp = parser_parseExpression();
        lexer_clearTokenList(tokens);
        parser_print(exp);
        parser_clearExpression(exp);

        // Flush output stream for debugging
        fflush(stdout);
    }
    else {
        char buffer[LINE_BUFFER_SIZE];
        printf("Welcome to the Lisp Interpreter REPL!\nUse Ctrl+C to exit\n");

        while (1){
            printf("\n>");

            // Read a line from stdin into the buffer
            // fgets(buffer, size, stream)
            // buffer: The character array to store the input
            // size: The maximum number of characters to read (including the null terminator)
            // stream: The input stream (stdin for standard input)
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                // fgets includes the newline character if there's space.
                // To remove it, you can find and replace it with a null terminator.
                size_t len = strlen(buffer);
                if (len > 0 && buffer[len-1] == '\n') {
                    buffer[len-1] = '\0';
                }

                lexer_scanTokens(buffer, tokens);
                parser_setList(tokens->first);
                SExpression* exp = parser_parseExpression();
                lexer_clearTokenList(tokens);
                parser_print(exp);
                parser_clearExpression(exp);
            } else {
                fprintf(stderr, "Error reading input.\n");
            }

            // Flush output stream for debugging
            fflush(stdout);
        }
    }

    return result;
}
