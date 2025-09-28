#include "stdio.h"

#include "util.h"
#include "sexpr.h"
#include "tester.h"

void runTests(TokenList* _tokens){
    printf("Running C tests...\n");

    SExpression *plus = atom((AtomType)A_ID, "+");
    SExpression *one = atom((AtomType)A_INT, "1");
    SExpression *two = atom((AtomType)A_INT, "2");

    // printf("Programmatically built: \n");
    // print(cons(plus, cons(one, cons(two, NULL))));

    // printf("\n\nVia lexing:\n");
    // runLine("(+ 1 2)", _tokens, 0);

    /// Testing Predicate functions
    printf("\nisDottedPair()\n");
    printf("%d:%d\n", UTIL_TRUE, isDottedPair(cons(one, two)));
    printf("%d:%d\n", UTIL_FALSE, isDottedPair(cons(one, cons(two, NULL))));
    printf("%d:%d\n", UTIL_FALSE, isDottedPair(one));
    printf("%d:%d\n", UTIL_FALSE, isDottedPair(NULL));
    
    printf("\nisFloat()\n");
    printf("%d:%d\n", UTIL_TRUE, isFloat(atom(A_FLT, "1.2")));
    printf("%d:%d\n", UTIL_FALSE, isFloat(one));
    printf("%d:%d\n", UTIL_FALSE, isFloat(NULL));
    printf("%d:%d\n", UTIL_FALSE, isFloat(cons(atom(A_FLT, "1.2"), atom(A_FLT, "3.4"))));

    printf("\nisIdentifier()\n");
    printf("%d:%d\n", UTIL_TRUE, isIdentifier(atom(A_ID, "PLUS")));
    printf("%d:%d\n", UTIL_TRUE, isIdentifier(plus));
    printf("%d:%d\n", UTIL_FALSE, isIdentifier(one));
    printf("%d:%d\n", UTIL_FALSE, isIdentifier(NULL));
    printf("%d:%d\n", UTIL_FALSE, isIdentifier(cons(atom(A_FLT, "1.2"), atom(A_FLT, "3.4"))));

    printf("\nisInt()\n");
    printf("%d:%d\n", UTIL_TRUE, isInt(atom(A_INT, "1")));
    printf("%d:%d\n", UTIL_TRUE, isInt(one));
    printf("%d:%d\n", UTIL_FALSE, isInt(NULL));
    printf("%d:%d\n", UTIL_FALSE, isInt(cons(atom(A_INT, "1"), atom(A_INT, "2"))));

    printf("\nisList()\n");
    printf("%d:%d\n", UTIL_TRUE, isList(cons(one, NULL)));
    printf("%d:%d\n", UTIL_TRUE, isList(cons(one, cons(two, NULL))));
    printf("%d:%d\n", UTIL_FALSE, isList(NULL));
    printf("%d:%d\n", UTIL_FALSE, isList(cons(one, two)));
    // I'm not sure what the expected behavior here should be, the expression contains
    // a list, but does that mean the expression itself is a list?
    printf("%d:%d - I'm not sure what the expected value here should be\n", UTIL_FALSE, isList(cons(cons(one, NULL), two)));

    printf("\nisNil()\n");
    printf("%d:%d\n", UTIL_TRUE, isNil(NULL));
    printf("%d:%d\n", UTIL_FALSE, isNil(one));
    printf("%d:%d\n", UTIL_FALSE, isNil(atom(A_STR, "Hello!")));
    printf("%d:%d\n", UTIL_FALSE, isNil(atom(A_ID, "GOODBYE")));
    printf("%d:%d\n", UTIL_FALSE, isNil(atom(A_INT, "1214")));
    printf("%d:%d\n", UTIL_FALSE, isNil(atom(A_FLT, "12.34")));
    
    printf("\nisNumber()\n");
    printf("%d:%d\n", UTIL_TRUE, isNumber(atom(A_INT, "1")));
    printf("%d:%d\n", UTIL_TRUE, isNumber(atom(A_FLT, "1.0")));
    printf("%d:%d\n", UTIL_FALSE, isNumber(atom(A_ID, "a")));
    printf("%d:%d\n", UTIL_FALSE, isNumber(atom(A_STR, "abc")));
    printf("%d:%d\n", UTIL_FALSE, isNumber(cons(one, two)));
    
    printf("\nisString()\n");
    printf("%d:%d\n", UTIL_TRUE, isString(atom(A_STR, "plus")));
    printf("%d:%d\n", UTIL_FALSE, isString(atom(A_ID, "PLUS")));
    printf("%d:%d\n", UTIL_FALSE, isString(one));
    printf("%d:%d\n", UTIL_FALSE, isString(plus));
    printf("%d:%d\n", UTIL_FALSE, isString(NULL));
    printf("%d:%d\n", UTIL_FALSE, isString(cons(atom(A_FLT, "1.2"), atom(A_FLT, "3.4"))));
}
