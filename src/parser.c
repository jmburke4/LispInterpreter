#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "sexpr.h"
#include "parser.h"
#include "../include/parser.h"  // This is here for intellisense

Token *currentToken = NULL;

void parser_advance() { if (currentToken != NULL) currentToken = (Token*)currentToken->next; }

SExpression *parser_clearExpression(SExpression *expr){
    if (expr != NULL){
        if (expr->type == (SExprType)CONS){
            parser_clearExpression(expr->cons.car);
            parser_clearExpression(expr->cons.cdr);
        }
        free(expr);
    }
    return NULL;
}

SExpression *parser_parseExpression() {
    if (currentToken == NULL) return NULL;

    SExpression *exp = NULL;
    switch (currentToken->type){
        case (TokenType)STRING:
            // Not sure where to determine whether its an identifier or a string
            // I can do this in the lexer by looking up reserved words, or all strings can have double quotes
            exp = atom(A_STR, currentToken->val);
            break;

        case (TokenType)INT:
            exp = atom(A_INT, currentToken->val);
            break;

        case (TokenType)FLOAT:
            exp = atom(A_FLT, currentToken->val);
            break;

        case (TokenType)OPEN_PAREN:
            parser_advance();
            return parser_parseList();

        case (TokenType)SINGLE_QUOTE:
            SExpression* quote = atom(A_ID, "quote\0");
            SExpression* quotedVal = atom(A_STR, currentToken->val + 1);
            exp = cons(quote, cons(quotedVal, NULL)); // Does this need to be NIL terminated or a dotted pair?
            break;

        case (TokenType)PLUS:
            exp = atom(A_ID, currentToken->val);
            break;

        case (TokenType)MINUS:
            exp = atom(A_ID, currentToken->val);
            break;

        case (TokenType)STAR:
            exp = atom(A_ID, currentToken->val);
            break;

        case (TokenType)SLASH:
            exp = atom(A_ID, currentToken->val);
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

void parser_setList(Token *head){ currentToken = head; }
