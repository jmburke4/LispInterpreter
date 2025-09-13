#include <stdio.h>
#include "util.h"
#include "lexer.h"
#include "parser.h"
#include "../include/parser.h" // This is here for intellisense

int main(int argc, char* argv[]) {
    int result = 0;
    TokenList* tokens = lexer_initTokenList();
    
    if (argc == 2){
        // Run filename passed by command line
        // ex. "./bin/tests/c1.txt"
        result = util_readFile((char*)argv[1], 256, tokens, lexer_scanTokens);
    }
    else {
        // Windows absolute path: "R:\\LispInterpreter\\tests\\c2.txt"
        result = util_readFile("./bin/tests/s1a.txt", 256, tokens, lexer_scanTokens);
    }

    lexer_printTokens(tokens);

    parser_setList(tokens->first);
    SExpression* exp = parser_parseExpression();
    parser_print(exp);

    return result;
}
