#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void print(SExpression *expr) {
    if (expr == NULL) {
        printf("()");
        return;
    }

    if (expr->type == (SExprType)ATOM) {
        switch (expr->atom.type){
            case A_STR:
            case A_ID:
                printf("%s", expr->atom.strVal);
                break;

            case A_INT:
                printf("%d", expr->atom.intVal);
                break;

            case A_FLT:
                printf("%f", expr->atom.floatVal);
                break;
        }
    } 
    else if (expr->type == (SExprType)CONS) {
        printf("(");
        while (expr != NULL && expr->type == CONS) {
            print(expr->cons.car);
            expr = expr->cons.cdr;
            if (expr != NULL) printf(" ");
        }
        if (expr != NULL) {
            printf(". ");
            print(expr);
        }
        printf(")");
    }
}
