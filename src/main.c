#include <stdio.h>
// #include "util.h"
#include "gll.h"
// #include "lexer.h"
// #include "parser.h"

gll_t* list;

int main() {
    // This is the Windows relative path
    // can also use absolute path "R:\\LispInterpreter\\tests\\s1.txt"
    //int result = util_readFile(".\\tests\\s1.txt", 256, util_printBuffer);

    list = gll_init();

    char* a = "A";
    char* b = "B";
    char* c = "str";

    // int a = 1;
    // int b = 2;
    // int c = 3;

    gll_pushBack(list, &a);
    gll_pushBack(list, &b);
    gll_pushBack(list, &c);

    gll_node_t* t = list->first;

    while (t != NULL){
        // int* t_int = (int*)t->data;
        // fprintf(stdout, "%d\n", *t_int);

        char** t_char = (char**)t->data;
        fprintf(stdout, "%s\n", *t_char);

        t = t->next;
    }

    return 0;
}
