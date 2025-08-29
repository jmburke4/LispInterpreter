#include <stdio.h>
#include "util.h"
#include "lexer.h"
//#include "parser.h"

int main() {
    int result = 0;
    // This is the Windows relative path
    // can also use absolute path "R:\\LispInterpreter\\tests\\s1.txt"
    result = util_readFile("R:\\LispInterpreter\\tests\\s1.txt", 256, lexer_scanTokens);

    return result;
}
