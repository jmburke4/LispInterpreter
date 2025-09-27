#include "lexer.h"

#ifndef PARSER_H
#define PARSER_H

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

/// @brief Creates a cons cell with two S-Expressions
/// @param a A pointer to the car S-expression
/// @param b A pointer to the cdr S-expression
/// @return A pointer to a new S-Expression
SExpression *cons(SExpression* a, SExpression* b);

/// @brief Advances the linked list to the next token
void parser_advance();

/// @brief Recursively frees the atoms in an S-Expression
/// @param expr The S-Expression to free
void parser_clearExpression(SExpression *expr);

/// @brief Initializes an Atom struct
/// @param type The type of Atom to initialize
/// @return The pointer to the new Atom struct
SExpression *parser_initAtom(AtomType type);

/// @brief Parses an S-Expression
/// @return An S-Expression
SExpression *parser_parseExpression();

/// @brief Parses a nested list of S-Expressions
/// @return An S-Expression
SExpression *parser_parseList();

/// @brief Returns the next token in the linked list but does not advance
/// @return The next token in the list
Token *parser_peek();

/// @brief Prints an S-Expression
/// @param expr The S-Expression to print
void parser_print(SExpression *expr);

/// @brief Initializes the parser global variable with a list of tokens
/// @param head The head of the list of tokens to use
void parser_setList(Token *head);

#endif
