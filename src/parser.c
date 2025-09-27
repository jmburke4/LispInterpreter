#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"
#include "../include/parser.h"  // This is here for intellisense

Token *currentToken = NULL;

void parser_advance() { if (currentToken != NULL) currentToken = (Token*)currentToken->next; }

Token *parser_peek() { return (Token*)currentToken->next; }

void parser_setList(Token *head){ currentToken = head; }

SExpression *parser_parseList() {
    if (currentToken == NULL || currentToken->type == (TokenType)CLOSE_PAREN){
        parser_advance();
        return NULL; // nil
    }
    
    SExpression *car = parser_parseExpression();
    SExpression *cdr = parser_parseList();

    SExpression *cell = malloc(sizeof(SExpression));
    cell->type = (SExprType)CONS;
    cell->cons.car = car;
    cell->cons.cdr = cdr;
    return cell;
}

SExpression *parser_parseExpression() {
    if (currentToken == NULL) return NULL;

    switch (currentToken->type){
        case (TokenType)STRING:
            // Not sure where to determine whether its an identifier or a string
            SExpression *astr = parser_initAtom(A_STR);
            astr->atom.strVal = malloc(sizeof(char*) * strlen(currentToken->val) + 1);
            strncpy(astr->atom.strVal, currentToken->val, strlen(currentToken->val) + 1);
            parser_advance();
            return astr;

        case (TokenType)INT:
            SExpression *aint = parser_initAtom(A_INT);
            aint->atom.intVal = (int)atoi(currentToken->val);
            parser_advance();
            return aint;

        case (TokenType)FLOAT:
            SExpression *aflt = parser_initAtom(A_FLT);
            aflt->atom.floatVal = (float)atof(currentToken->val);
            parser_advance();
            return aflt;

        case (TokenType)OPEN_PAREN:
            parser_advance();
            return parser_parseList();

        case (TokenType)SINGLE_QUOTE:
            SExpression* quote = parser_initAtom(A_ID);
            quote->atom.strVal = malloc(sizeof(char*) * strlen("quote") + 1);
            strncpy(quote->atom.strVal, "quote\0", strlen("quote") + 1);
            
            SExpression* quotedVal = parser_initAtom(A_STR);
            quotedVal->atom.strVal = malloc(sizeof(char*) * strlen(currentToken->val) + 1);
            strncpy(quotedVal->atom.strVal, currentToken->val + 1, strlen(currentToken->val) + 1);

            parser_advance();
            return cons(quote, quotedVal);

        default:
            fprintf(stderr, "Unhandled TokenType: %d\n", currentToken->type);
            parser_advance();
            break;
    }
    return NULL;
}

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

void parser_clearExpression(SExpression *expr){
    if (expr != NULL){
        if (expr->type == (SExprType)CONS){
            parser_clearExpression(expr->cons.car);
            parser_clearExpression(expr->cons.cdr);
        }
        free(expr);
    }
}

SExpression *parser_initAtom(AtomType type){
    SExpression *atom = malloc(sizeof(SExpression));
    atom->type = (SExprType)ATOM;
    atom->atom.type = type;
    return atom;
}

SExpression *cons(SExpression* a, SExpression* b){
    SExpression *new = malloc(sizeof(SExpression));
    new->type = (SExprType)CONS;
    new->cons.car = a;
    new->cons.cdr = b;
    return new;
}
