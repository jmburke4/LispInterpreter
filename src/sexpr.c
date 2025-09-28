#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "sexpr.h"

SExpression *atom(AtomType type, char *val){
    SExpression *atom = malloc(sizeof(SExpression));
    atom->type = (SExprType)ATOM;
    atom->atom.type = type;

    switch (type){
        case (AtomType)A_STR:
        case (AtomType)A_ID:
            atom->atom.strVal = malloc(sizeof(char*) * strlen((char*)val) + 1);
            strncpy(atom->atom.strVal, (char*)val, strlen((char*)val) + 1);
            break;

        case (AtomType)A_INT:
            atom->atom.intVal = (int)atoi(val);
            break;

        case (AtomType)A_FLT:
            atom->atom.floatVal = (float)atof(val);
            break;

        default:
            fprintf(stderr, "Type: %d is an unhandled AtomType\n", type);
            break;
    }

    return atom;
}

SExpression *cons(SExpression* car, SExpression* cdr){
    SExpression *new = malloc(sizeof(SExpression));
    new->type = (SExprType)CONS;
    new->cons.car = car;
    new->cons.cdr = cdr;
    return new;
}

SExpression *eval(SExpression *exp){
    return exp;
}

int isDottedPair(SExpression *exp){
    if (isNil(exp) == UTIL_TRUE) return UTIL_FALSE;
    if (exp->type != (SExprType)CONS) return UTIL_FALSE;
    if (isNil(exp->cons.car) == UTIL_FALSE && isNil(exp->cons.cdr) == UTIL_FALSE){
        if (exp->cons.car->type == (SExprType)ATOM && exp->cons.cdr->type == (SExprType)ATOM) return UTIL_TRUE;
    }
    return UTIL_FALSE;
}

int isFloat(SExpression *exp){
    if (isNil(exp) == UTIL_TRUE) return UTIL_FALSE;
    if (exp->type != (SExprType)ATOM) return UTIL_FALSE;
    if (exp->atom.type != (AtomType)A_FLT) return UTIL_FALSE;
    return UTIL_TRUE;
}

int isIdentifier(SExpression *exp){
    if (isNil(exp) == UTIL_TRUE) return UTIL_FALSE;
    if (exp->type != (SExprType)ATOM) return UTIL_FALSE;
    if (exp->atom.type != (AtomType)A_ID) return UTIL_FALSE;
    return UTIL_TRUE;
}

int isInt(SExpression *exp){
    if (isNil(exp) == UTIL_TRUE) return UTIL_FALSE;
    if (exp->type != (SExprType)ATOM) return UTIL_FALSE;
    if (exp->atom.type != (AtomType)A_INT) return UTIL_FALSE;
    return UTIL_TRUE;
}

int isList(SExpression *exp){
    if (isNil(exp) == UTIL_TRUE) return UTIL_FALSE;
    if (isDottedPair(exp) == UTIL_TRUE) return UTIL_FALSE;
    if (exp->type == (SExprType)ATOM) return UTIL_FALSE;
    if (exp->type == (SExprType)CONS && isNil(exp->cons.cdr) == UTIL_TRUE) return UTIL_TRUE;
    return isList(exp->cons.car) || isList(exp->cons.cdr);
}

int isNil(SExpression *exp){
    if (exp == NULL) return UTIL_TRUE;
    return UTIL_FALSE;
}

int isNumber(SExpression *exp){ return isFloat(exp) || isInt(exp); }

int isString(SExpression *exp){
    if (isNil(exp) == UTIL_TRUE) return UTIL_FALSE;
    if (exp->type != (SExprType)ATOM) return UTIL_FALSE;
    if (exp->atom.type != (AtomType)A_STR) return UTIL_FALSE;
    return UTIL_TRUE;
}

int toBool(SExpression *exp){
    if (isNil(exp) == UTIL_TRUE) return UTIL_FALSE;
    return UTIL_TRUE;
}

void print(SExpression *exp) {
    if (exp == NULL) {
        printf("()");
        return;
    }

    if (exp->type == (SExprType)ATOM) {
        switch (exp->atom.type){
            case A_STR:
            case A_ID:
                printf("%s", exp->atom.strVal);
                break;

            case A_INT:
                printf("%d", exp->atom.intVal);
                break;

            case A_FLT:
                printf("%f", exp->atom.floatVal);
                break;
        }
    } 
    else if (exp->type == (SExprType)CONS) {
        printf("(");
        while (exp != NULL && exp->type == CONS) {
            print(exp->cons.car);
            exp = exp->cons.cdr;
            if (exp != NULL) printf(" ");
        }
        if (exp != NULL) {
            printf(". ");
            print(exp);
        }
        printf(")");
    }
}
