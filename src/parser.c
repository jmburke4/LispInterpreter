#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"
#include "../include/parser.h"  // This is here for intellisense

Token *currentToken = NULL;

SExpression *cons(SExpression* a, SExpression* b){
    SExpression *new = malloc(sizeof(SExpression));
    new->type = (SExprType)CONS;
    new->cons.car = a;
    new->cons.cdr = b;
    return new;
}

void parser_advance() { if (currentToken != NULL) currentToken = (Token*)currentToken->next; }

void parser_clearExpression(SExpression *expr){
    if (expr != NULL){
        if (expr->type == (SExprType)CONS){
            parser_clearExpression(expr->cons.car);
            parser_clearExpression(expr->cons.cdr);
        }
        free(expr);
    }
}

SExpression *parser_initAtom(AtomType type, char *val){
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

SExpression *parser_parseExpression() {
    if (currentToken == NULL) return NULL;

    SExpression *exp = NULL;
    switch (currentToken->type){
        case (TokenType)STRING:
            // Not sure where to determine whether its an identifier or a string
            exp = parser_initAtom(A_STR, currentToken->val);
            break;

        case (TokenType)INT:
            exp = parser_initAtom(A_INT, currentToken->val);
            break;

        case (TokenType)FLOAT:
            exp = parser_initAtom(A_FLT, currentToken->val);
            break;

        case (TokenType)OPEN_PAREN:
            parser_advance();
            return parser_parseList();

        case (TokenType)SINGLE_QUOTE:
            SExpression* quote = parser_initAtom(A_ID, "quote\0");
            SExpression* quotedVal = parser_initAtom(A_STR, currentToken->val + 1);
            exp = cons(quote, cons(quotedVal, NULL)); // Does this need to be NIL terminated or a dotted pair?
            break;

        case (TokenType)PLUS:
            exp = parser_initAtom(A_ID, currentToken->val);
            break;

        case (TokenType)MINUS:
            exp = parser_initAtom(A_ID, currentToken->val);
            break;

        case (TokenType)STAR:
            exp = parser_initAtom(A_ID, currentToken->val);
            break;

        case (TokenType)SLASH:
            exp = parser_initAtom(A_ID, currentToken->val);
            break;

        default:
            fprintf(stderr, "Unhandled TokenType: %d\n", currentToken->type);
            break;
    }
    parser_advance();
    return exp;
}

SExpression *parser_parseList() {
    if (currentToken == NULL || currentToken->type == (TokenType)CLOSE_PAREN){
        parser_advance();
        return NULL; // nil
    }
    
    SExpression *car = parser_parseExpression();
    SExpression *cdr = parser_parseList();

    return cons(car, cdr);
}

Token *parser_peek() { return (Token*)currentToken->next; }

void parser_print(SExpression *expr) {
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
            parser_print(expr->cons.car);
            expr = expr->cons.cdr;
            if (expr != NULL) printf(" ");
        }
        if (expr != NULL) {
            printf(". ");
            parser_print(expr);
        }
        printf(")");
    }
}

void parser_setList(Token *head){ currentToken = head; }
