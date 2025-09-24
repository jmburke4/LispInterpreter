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

    if (currentToken->type == (TokenType)TATOM){
        SExpression *atom = malloc(sizeof(SExpression));
        atom->type = (SExprType)ATOM;
        atom->atom = malloc(sizeof(char*) * strlen(currentToken->val));
        strncpy(atom->atom, currentToken->val, strlen(currentToken->val) + 1);
        parser_advance();
        return atom;
    }

    if (currentToken->type == (TokenType)OPEN_PAREN){
        parser_advance();
        return parser_parseList();
    }

    return NULL; // nil
}

void parser_print(SExpression *expr) {
    if (expr == NULL) {
        printf("()");
        return;
    }

    if (expr->type == (SExprType)ATOM) {
        fprintf(stdout, "%s", expr->atom);
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
