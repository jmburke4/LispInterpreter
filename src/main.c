#include <stdio.h>
#include "util.h"
#include "lexer.h"
//#include "parser.h"

int main(int argc, char *argv[]) {
    int result = 0;
    TokenList* tokens = lexer_initTokenList();
    
    if (argc == 2){
        // Run filename passed by command line
        // ex. "./bin/tests/c1.txt"
        result = util_readFile((char*)argv[1], 256, tokens, lexer_scanTokens);
    }
    else {
        // Windows absolute path: "R:\\LispInterpreter\\tests\\c2.txt"
        result = util_readFile("./bin/tests/c2.txt", 256, tokens, lexer_scanTokens);
    }

    Token* head = (Token*)tokens->first;
    while (head != NULL){
        fprintf(stdout, "LIST: %s\n", head->val);
        head = (Token*)head->next;
    }

    fprintf(stdout, "Lexed %d tokens\n", tokens->size);

    return result;
}
