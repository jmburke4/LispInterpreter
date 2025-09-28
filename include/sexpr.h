#ifndef SEXPR_H
#define SEXPR_H

typedef enum { ATOM, CONS } SExprType;
typedef enum { A_ID, A_STR, A_INT, A_FLT } AtomType;

typedef struct {
    AtomType type;
    union {
        char *strVal;
        int intVal;
        float floatVal;
    };
} Atom;

typedef struct SExpression {
    SExprType type;
    union {
        Atom atom; // for symbols, numbers, strings
        struct {
            struct SExpression *car;
            struct SExpression *cdr;
        } cons;
    };
} SExpression;

/// @brief Initializes an Atom struct
/// @param type The type of Atom to initialize
/// @param val A pointer to a C-String that will be casted to the correct data value
/// @return The pointer to the new Atom struct
SExpression *atom(AtomType type, char *val);

/// @brief Creates a cons cell with two S-Expressions
/// @param car A pointer to the car S-expression
/// @param cdr A pointer to the cdr S-expression
/// @return A pointer to a new S-Expression
SExpression *cons(SExpression* car, SExpression* cdr);

/// @brief Prints an S-Expression
/// @param expr The S-Expression to print
void print(SExpression *expr);

#endif
