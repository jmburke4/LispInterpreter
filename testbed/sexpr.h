#ifndef SEXPR_H
#define SEXPR_H

struct Atom;
struct Cons;
struct SExpression;

typedef struct {
    union {
        char *strVal;
        int intVal;
        float floatVal;
    };
} Atom;

typedef struct {
    SExpression *car;
    SExpression *cdr;
} Cons;

typedef struct {
    Atom atom;
    Cons cons;
} SExpression;

SExpression *car();

SExpression *cdr();

SExpression *cons(SExpression *car, SExpression *cdr);

SExpression *eval(SExpression *exp);

void print(SExpression *exp);

#endif
