#include <stdlib.h>

typedef enum { ATOM, CONS, NIL } SExprType;

typedef struct SExpression {
    SExprType type;
    union {
        char *atom; // for symbols, numbers, strings
        struct {
            struct SExpression *car;
            struct SExpression *cdr;
        } cons;
    };
} SExpression;

typedef enum { TOKEN_LPAREN, TOKEN_RPAREN, TOKEN_ATOM } TokenType;

typedef struct Token {
    TokenType type;
    char *value; // only used for TOKEN_ATOM
    struct Token *next;
} Token;

Token *current_token;

void advance() {
    if (current_token != NULL)
        current_token = current_token->next;
}

SExpression *parse_s_expression();

SExpression *parse_list() {
    if (current_token == NULL || current_token->type == TOKEN_RPAREN) {
        advance(); // consume ')'
        return NULL; // represents nil
    }

    SExpression *car = parse_s_expression();
    SExpression *cdr = parse_list();

    SExpression *cell = malloc(sizeof(SExpression));
    cell->type = CONS;
    cell->cons.car = car;
    cell->cons.cdr = cdr;
    return cell;
}

SExpression *parse_s_expression() {
    if (current_token == NULL) return NULL;

    if (current_token->type == TOKEN_ATOM) {
        SExpression *atom = malloc(sizeof(SExpression));
        atom->type = ATOM;
        atom->atom = strdup(current_token->value);
        advance();
        return atom;
    }

    if (current_token->type == TOKEN_LPAREN) {
        advance(); // consume '('
        return parse_list();
    }

    // Unexpected token
    return NULL;
}

void print_s_expression(SExpression *expr) {
    if (expr == NULL) {
        printf("()");
        return;
    }

    if (expr->type == ATOM) {
        printf("%s", expr->atom);
    } else if (expr->type == CONS) {
        printf("(");
        while (expr != NULL && expr->type == CONS) {
            print_s_expression(expr->cons.car);
            expr = expr->cons.cdr;
            if (expr != NULL) printf(" ");
        }
        if (expr != NULL) {
            printf(". ");
            print_s_expression(expr);
        }
        printf(")");
    }
}
