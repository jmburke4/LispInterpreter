#include <stdio.h>
#include "util.h"
#include "lexer.h"
//#include "parser.h"

int main() {
    int result = 0;
    TokenList* tokens = lexer_initTokenList();

    // This is the Windows relative path
    // can also use absolute path "R:\\LispInterpreter\\tests\\s1.txt"
    result = util_readFile("R:\\LispInterpreter\\tests\\rl.txt", 256, tokens, lexer_scanTokens);

    Token* head = (Token*)tokens->first;
    while (head != NULL){
        fprintf(stdout, "LIST: %s\n", head->val);
        head = (Token*)head->next;
    }

    return result;
}
