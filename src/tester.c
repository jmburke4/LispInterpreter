#include "stdio.h"

#include "types.h"
#include "util.h"
#include "parser.h"
#include "sexpr.h"
#include "env.h"
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

    /// Testing SExpr.h functions

    printf("\nadd()");
    printf("\n3\t");
    print(add(cons(one, two)));
    printf("\n3.0\t");
    print(add(cons(atom(A_FLT, "1.0"), atom(A_FLT, "2.0"))));
    printf("\n5.0\t");
    print(add(cons(atom(A_INT, "1"), atom(A_FLT, "4.0"))));
    printf("\n()\t");
    print(add(NULL));
    printf("\n()\t");
    print(add(one));
    printf("\n6\t");    // (+ 1 (+ 2 3))
    print(add(cons(atom(A_INT, "1"), add(cons(atom(A_INT, "2"), atom(A_INT, "3"))))));
    printf("\n6.0\t");    // (+ 1 (+ 2.0 3))
    print(add(cons(atom(A_INT, "1"), add(cons(atom(A_FLT, "2.0"), atom(A_INT, "3"))))));
    printf("\n()\t");
    print(add(cons(atom(A_INT, "1"), add(cons(atom(A_STR, "2.0"), atom(A_INT, "3"))))));
    printf("\n");

    printf("\ndivide()");
    printf("\n2\t");
    print(divide(cons(two, one)));
    printf("\n0\t"); // ?? 1 / 2 = 0? Integer division
    print(divide(cons(one, two)));
    printf("\n2.0\t");
    print(divide(cons(atom(A_FLT, "2.0"), atom(A_FLT, "1.0"))));
    printf("\n0.5\t");
    print(divide(cons(atom(A_FLT, "1.0"), atom(A_FLT, "2.0"))));
    printf("\n-0.333\t"); // -1/3
    print(divide(cons(atom(A_INT, "1"), atom(A_FLT, "-3.0"))));
    printf("\n()\t");
    print(divide(NULL));
    printf("\n()\t");
    print(divide(one));
    printf("\n()\t");
    print(divide(cons(atom(A_STR, "1"), atom(A_FLT, "-3.0"))));
    printf("\n()\t");
    print(divide(cons(atom(A_INT, "1"), atom(A_INT, "0"))));
    printf("\n()\t");
    print(divide(cons(atom(A_INT, "1"), atom(A_FLT, "0.0"))));
    printf("\n18\t");
    print(divide(cons(atom(A_INT, "36"), divide(cons(atom(A_INT, "6"), atom(A_INT, "3"))))));
    printf("\n-0.5\t");
    print(divide(cons(atom(A_INT, "-1"), divide(cons(atom(A_FLT, "6.0"), atom(A_INT, "3"))))));
    printf("\n");

    printf("\neq()");
    printf("\ntrue\t");
    print(eq(cons(one, one)));
    printf("\n()\t");
    print(eq(cons(one, two)));
    printf("\n()\t");
    print(eq(NULL));
    printf("\n()\t");
    print(eq(cons(atom(A_STR, "Hello"), atom(A_STR, "HELLO"))));
    printf("\ntrue\t");
    print(eq(cons(atom(A_STR, "Hello"), atom(A_STR, "Hello"))));
    printf("\n()\t");
    print(eq(cons(atom(A_ID, "Hello"), atom(A_ID, "HELLO"))));
    printf("\ntrue\t");
    print(eq(cons(atom(A_ID, "Hello"), atom(A_ID, "Hello"))));
    printf("\n()\t");
    print(eq(cons(atom(A_ID, "Hello"), atom(A_STR, "Hello"))));
    printf("\n");

    printf("\ngt()");
    printf("\ntrue\t");
    print(gt(cons(atom(A_INT, "3"), atom(A_INT, "2"))));
    printf("\n()\t");
    print(gt(cons(atom(A_INT, "1"), atom(A_INT, "2"))));
    printf("\ntrue\t");
    print(gt(cons(atom(A_FLT, "3.0"), atom(A_FLT, "2.0"))));
    printf("\n()\t");
    print(gt(cons(atom(A_FLT, "1.0"), atom(A_FLT, "2.0"))));
    printf("\ntrue\t");
    print(gt(cons(atom(A_FLT, "3.0"), atom(A_INT, "2"))));
    printf("\ntrue\t");
    print(gt(cons(atom(A_INT, "30"), multiply(cons(atom(A_FLT, "10.0"), atom(A_INT, "2"))))));
    printf("\n()\t");
    print(gt(cons(atom(A_INT, "3"), atom(A_FLT, "3.0"))));
    printf("\n");

    printf("\ngte()");
    printf("\ntrue\t");
    print(gte(cons(atom(A_INT, "3"), atom(A_INT, "2"))));
    printf("\n()\t");
    print(gte(cons(atom(A_INT, "1"), atom(A_INT, "2"))));
    printf("\ntrue\t");
    print(gte(cons(atom(A_FLT, "3.0"), atom(A_FLT, "2.0"))));
    printf("\ntrue\t");
    print(gte(cons(atom(A_FLT, "3.0"), atom(A_FLT, "2.0"))));
    printf("\ntrue\t");
    print(gte(cons(atom(A_FLT, "3.0"), atom(A_INT, "2"))));
    printf("\ntrue\t");
    print(gte(cons(atom(A_INT, "30"), multiply(cons(atom(A_FLT, "10.0"), atom(A_INT, "2"))))));
    printf("\ntrue\t");
    print(gte(cons(atom(A_INT, "3"), atom(A_FLT, "3.0"))));
    printf("\ntrue\t");
    print(gte(cons(atom(A_INT, "3"), atom(A_INT, "3"))));
    printf("\ntrue\t");
    print(gte(cons(atom(A_FLT, "3.0"), atom(A_FLT, "3.0"))));
    printf("\n");

    printf("\nisAtom()\n");
    printf("%d:%d\n", UTIL_TRUE, isAtom(plus));
    printf("%d:%d\n", UTIL_TRUE, isAtom(one));
    printf("%d:%d\n", UTIL_TRUE, isAtom(two));
    printf("%d:%d - Is nil technically an atom?\n", UTIL_FALSE, isAtom(NULL));
    printf("%d:%d\n", UTIL_FALSE, isAtom(cons(plus, one)));
    printf("%d:%d\n", UTIL_FALSE, isAtom(cons(plus, cons(one, cons(two, NULL)))));

    printf("\nisCons()\n");
    printf("%d:%d\n", UTIL_TRUE, isCons(cons(plus, one)));
    printf("%d:%d\n", UTIL_TRUE, isCons(cons(plus, cons(one, cons(two, NULL)))));
    printf("%d:%d\n", UTIL_FALSE, isCons(plus));
    printf("%d:%d\n", UTIL_FALSE, isCons(NULL));
    printf("%d:%d\n", UTIL_FALSE, isCons(one));

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

    printf("\nlt()");
    printf("\ntrue\t");
    print(lt(cons(atom(A_INT, "1"), atom(A_INT, "2"))));
    printf("\n()\t");
    print(lt(cons(atom(A_INT, "3"), atom(A_INT, "2"))));
    printf("\ntrue\t");
    print(lt(cons(atom(A_FLT, "1.0"), atom(A_FLT, "2.0"))));
    printf("\n()\t");
    print(lt(cons(atom(A_FLT, "3.0"), atom(A_FLT, "2.0"))));
    printf("\ntrue\t");
    print(lt(cons(atom(A_FLT, "1.0"), atom(A_INT, "2"))));
    printf("\ntrue\t");
    print(lt(cons(atom(A_INT, "13"), multiply(cons(atom(A_FLT, "10.0"), atom(A_INT, "2"))))));
    printf("\n()\t");
    print(lt(cons(atom(A_INT, "3"), atom(A_FLT, "3.0"))));
    printf("\n");

    printf("\nlte()");
    printf("\ntrue\t");
    print(lte(cons(atom(A_INT, "1"), atom(A_INT, "2"))));
    printf("\n()\t");
    print(lte(cons(atom(A_INT, "3"), atom(A_INT, "2"))));
    printf("\ntrue\t");
    print(lte(cons(atom(A_FLT, "1.0"), atom(A_FLT, "2.0"))));
    printf("\n()\t");
    print(lte(cons(atom(A_FLT, "3.0"), atom(A_FLT, "2.0"))));
    printf("\ntrue\t");
    print(lte(cons(atom(A_FLT, "1.0"), atom(A_INT, "2"))));
    printf("\ntrue\t");
    print(lte(cons(atom(A_INT, "13"), multiply(cons(atom(A_FLT, "10.0"), atom(A_INT, "2"))))));
    printf("\ntrue\t");
    print(lte(cons(atom(A_INT, "3"), atom(A_FLT, "3.0"))));
    printf("\ntrue\t");
    print(lte(cons(atom(A_INT, "3"), atom(A_INT, "3"))));
    printf("\ntrue\t");
    print(lte(cons(atom(A_FLT, "3.0"), atom(A_FLT, "3.0"))));
    printf("\n");

    printf("\nmodulo()");
    printf("\n0\t");
    print(modulo(cons(two, one)));
    printf("\n1\t");
    print(modulo(cons(one, two)));
    printf("\n()\t");
    print(modulo(cons(atom(A_FLT, "2.0"), atom(A_FLT, "1.0"))));
    printf("\n1\t"); // -1/3
    print(modulo(cons(atom(A_INT, "1"), atom(A_INT, "-3"))));
    printf("\n2\t"); // -1/3
    print(modulo(cons(atom(A_INT, "17"), atom(A_INT, "-3"))));
    printf("\n()\t");
    print(modulo(NULL));
    printf("\n()\t");
    print(modulo(one));
    printf("\n()\t");
    print(modulo(cons(atom(A_INT, "1"), atom(A_INT, "0"))));
    printf("\n()\t");
    print(modulo(cons(atom(A_STR, "1"), atom(A_INT, "0"))));
    printf("\n()\t"); // The nested modulo returns 0
    print(modulo(cons(atom(A_INT, "36"), modulo(cons(atom(A_INT, "6"), atom(A_INT, "3"))))));
    printf("\n");

    printf("\nmultiply()");
    printf("\n2\t");
    print(multiply(cons(two, one)));
    printf("\n2\t");
    print(multiply(cons(one, two)));
    printf("\n2.0\t");
    print(multiply(cons(atom(A_FLT, "2.0"), atom(A_FLT, "1.0"))));
    printf("\n-3.0\t");
    print(multiply(cons(atom(A_INT, "1"), atom(A_FLT, "-3.0"))));
    printf("\n()\t");
    print(multiply(NULL));
    printf("\n()\t");
    print(multiply(one));
    printf("\n18\t");
    print(multiply(cons(atom(A_INT, "1"), multiply(cons(atom(A_INT, "6"), atom(A_INT, "3"))))));
    printf("\n-6.0\t");
    print(multiply(cons(atom(A_INT, "-1"), multiply(cons(atom(A_FLT, "2.0"), atom(A_INT, "3"))))));
    printf("\n0\t");
    print(multiply(cons(one, atom(A_INT, "0"))));
    printf("\n()\t");
    print(multiply(cons(one, atom(A_STR, "0"))));
    printf("\n0.0\t");
    print(multiply(cons(atom(A_FLT, "0.0"), two)));
    printf("\n");

    printf("\nnot()");
    printf("\ntrue\t");
    print(not(NULL));
    printf("\n()\t");
    print(not(atom(A_INT, "1")));
    printf("\n()\t");
    print(not(eq(cons(atom(A_STR, "Hello"), atom(A_STR, "Hello")))));
    printf("\ntrue\t");
    print(not(eq(cons(atom(A_STR, "Hello"), atom(A_STR, "HELLO")))));
    printf("\n");

    printf("\nsubtract()");
    printf("\n1\t");
    print(subtract(cons(two, one)));
    printf("\n-1\t");
    print(subtract(cons(one, two)));
    printf("\n1.0\t");
    print(subtract(cons(atom(A_FLT, "2.0"), atom(A_FLT, "1.0"))));
    printf("\n-3.0\t");
    print(subtract(cons(atom(A_INT, "1"), atom(A_FLT, "4.0"))));
    printf("\n()\t");
    print(subtract(cons(atom(A_ID, "1"), atom(A_FLT, "4.0"))));
    printf("\n()\t");
    print(subtract(NULL));
    printf("\n()\t");
    print(subtract(one));
    printf("\n-2\t");
    print(subtract(cons(atom(A_INT, "1"), subtract(cons(atom(A_INT, "6"), atom(A_INT, "3"))))));
    printf("\n2.0\t");
    print(subtract(cons(atom(A_INT, "1"), subtract(cons(atom(A_FLT, "2.0"), atom(A_INT, "3"))))));
    printf("\n");
}

void testEnvironment(){
    Environment *global = initEnvironment();

    SExpression *eq = atom(A_ID, "eq");
    SExpression *plus = atom(A_ID, "+");
    SExpression *three = atom(A_INT, "3");
    SExpression *five = atom(A_INT, "5");
    SExpression *eight = atom(A_INT, "8");

    SExpression *set = atom(A_ID, "set");
    SExpression *a = atom(A_STR, "a");
    SExpression *evala = atom(A_ID, "a");
    
    /// Expression building and evaluating

    SExpression *exp = cons(set, cons(a, eight));
    printf("\n(set a 8) ; -> 8 : ");
    print(eval(exp, global));

    exp = evala;
    printf("\n(a) ; -> 8 : ");
    print(eval(exp, global));

    exp = cons(eq, cons(evala, eight));
    printf("\n(eq a 8) ; -> true : ");
    print(eval(exp, global));

    exp = cons(eq, cons(cons(evala, NULL), eight));
    printf("\n(eq (a ()) 8) ; -> true : ");
    print(eval(exp, global));

    exp = cons(eq, cons(eight, evala));
    printf("\n(eq 8 a) ; -> true : ");
    print(eval(exp, global));

    exp = cons(eq, cons(eight, cons(plus, cons(three, five))));
    printf("\n(eq 8 (+ 3 5)) ; -> true : ");
    print(eval(exp, global));

    exp = cons(eq, cons(cons(plus, cons(three, five)), eight));
    printf("\n(eq (+ 3 5) 8) ; -> true : ");
    print(eval(exp, global));
}
