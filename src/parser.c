#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "sexpr.h"
#include "parser.h"

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
        case (TokenType)STRING: // These are single word identifiers, strings are handled via DOUBLE_QUOTE
            Token *prev = (Token*)currentToken->prev;
            if (prev->type == OPEN_PAREN && prev->prev != NULL) prev = (Token*)prev->prev;
            // Treat any token that comes directly after the set command as a string instead
            // of an identifier so that it is not evaluated later
            if (prev->type == STRING && strcmp(prev->val, "set") == 0) exp = atom(A_STR, currentToken->val);
            else exp = atom(A_ID, currentToken->val);
            break;

        case (TokenType)INT:
            exp = atom(A_INT, currentToken->val);
            break;

        case (TokenType)FLOAT:
            exp = atom(A_FLT, currentToken->val);
            break;

        case (TokenType)OPEN_PAREN:
            parser_advance();
            exp = parser_parseExpression();
            break;

        case (TokenType)CLOSE_PAREN:
            return exp;

        case (TokenType)SINGLE_QUOTE:
            SExpression* quote = atom(A_ID, "quote\0");
            SExpression* quotedVal = atom(A_STR, currentToken->val + 1);
            // Does this need to be NIL terminated or a dotted pair?
            exp = cons(quote, cons(quotedVal, NULL));
            break;

        case (TokenType)DOUBLE_QUOTE:
        case (TokenType)PLUS:
        case (TokenType)MINUS:
        case (TokenType)STAR:
        case (TokenType)SLASH:
        case (TokenType)MOD:
        case (TokenType)EQ:
        case (TokenType)NOTEQ:
        case (TokenType)LT:
        case (TokenType)LTE:
        case (TokenType)GT:
        case (TokenType)GTE:
            exp = atom(A_ID, currentToken->val);
            break;

        default:
            fprintf(stderr, "Unhandled TokenType: %d\n", currentToken->type);
            break;
    }
    parser_advance();
    return cons(exp, parser_parseExpression());
}

void parser_setList(Token *head){ currentToken = head; }
