#include <stdio.h>
#include <string.h>
#include "util.h"
#include "lexer.h"
#include "parser.h"
#include "../include/parser.h" // This is here for intellisense

#define LINE_BUFFER_SIZE 256

int main(int argc, char *argv[]) {
    int result = 0;
    TokenList *tokens = lexer_initTokenList();
    char buffer[LINE_BUFFER_SIZE];

    if (argc == 2){
        FILE *fptr = fopen((char*)argv[1], "r");
        if (fptr == NULL) {
            fprintf(stderr, "Error for filepath: \'%s\'\n", (char*)argv[1]);
            return UTIL_FAILURE;
        }

        while (fgets(buffer, sizeof(buffer), fptr) != NULL){
            // fgets includes the newline character if there's space.
            // To remove it, you can find and replace it with a null terminator.
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len-1] == '\n') {
                buffer[len-1] = '\0';
            }

            lexer_scanTokens(buffer, tokens);
            if (tokens->size > 0){
                printf("\n>%s\n", buffer);
                
                lexer_printTokens(tokens);
                parser_setList(tokens->first);
                SExpression *exp = parser_parseExpression();
                lexer_clearTokenList(tokens);
                parser_print(exp);
                parser_clearExpression(exp);
                
                // Flush output stream for debugging
                printf("\n");
                fflush(stdout);
            }
        }

        if (!feof(fptr)) perror("Error reading file");
        if (fclose(fptr) != 0) perror("Error closing file");
    }
    else {
        printf("Welcome to the Lisp Interpreter REPL!\nUse Ctrl+C to exit\n");

        while (1){
            printf("\n>");

            if (fgets(buffer, sizeof(buffer), stdin) != NULL){
                // fgets includes the newline character if there's space.
                // To remove it, you can find and replace it with a null terminator.
                size_t len = strlen(buffer);
                if (len > 0 && buffer[len-1] == '\n') {
                    buffer[len-1] = '\0';
                }

                lexer_scanTokens(buffer, tokens);
                if (tokens->size > 0){
                    parser_setList(tokens->first);
                    SExpression *exp = parser_parseExpression();
                    lexer_clearTokenList(tokens);
                    parser_print(exp);
                    parser_clearExpression(exp);
                }
            } 
            else {
                fprintf(stderr, "Error reading input.\n");
            }

            // Flush output stream for debugging
            printf("\n");
            fflush(stdout);
        }
    }

    return result;
}
