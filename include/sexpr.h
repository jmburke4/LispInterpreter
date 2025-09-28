#ifndef SEXPR_H
#define SEXPR_H

/// @brief An enum for the type of an ```SExpression```
typedef enum { ATOM, CONS } SExprType;

/// @brief An enum for the type of an ```Atom```
typedef enum { A_ID, A_STR, A_INT, A_FLT } AtomType;

/// @brief A struct representing an Atom in Lisp
typedef struct {
    AtomType type;
    union {
        char *strVal;
        int intVal;
        float floatVal;
    };
} Atom;

/// @brief A struct representing an S-Expression in Lisp
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

/// @brief Creates a cons cell with two ```SExpression```s
/// @param car A pointer to the car ```SExpression```
/// @param cdr A pointer to the cdr ```SExpression```
/// @return A pointer to a new ```SExpression```
SExpression *cons(SExpression* car, SExpression* cdr);

/// @brief Recursively evaluates an ```SExpression```
/// @param exp The ```SExpression``` to evaluate
/// @return The evaluated ```SExpression```
SExpression *eval(SExpression *exp);

/// @brief Checks if an ```SExpression``` is an ```Atom```
/// @param exp The ```SExpression``` to check
/// @return ```UTIL_TRUE``` or ```UTIL_FALSE```
int isAtom(SExpression *exp);

/// @brief Checks if an ```SExpression``` is a ```Cons``` cell
/// @param exp The ```SExpression``` to check
/// @return ```UTIL_TRUE``` or ```UTIL_FALSE```
int isCons(SExpression *exp);

/// @brief Checks if an ```SExpression``` is a dotted pair or not
/// @param exp The ```SExpression``` to check
/// @return ```UTIL_TRUE``` or ```UTIL_FALSE```
int isDottedPair(SExpression *exp);

/// @brief Checks if an ```SExpression``` is an ```Atom``` of type ```float```
/// @param exp The ```SExpression``` to check
/// @return ```UTIL_TRUE``` or ```UTIL_FALSE```
int isFloat(SExpression *exp);

/// @brief Checks if an ```SExpression``` is an ```Atom``` of type ```A_ID```
/// @param exp The ```SExpression``` to check
/// @return ```UTIL_TRUE``` or ```UTIL_FALSE```
int isIdentifier(SExpression *exp);

/// @brief Checks if an ```SExpression``` is an ```Atom``` of type ```int```
/// @param exp The ```SExpression``` to check
/// @return ```UTIL_TRUE``` or ```UTIL_FALSE```
int isInt(SExpression *exp);

/// @brief Checks if an ```SExpression``` is a ```nil``` terminated list
/// @param exp The ```SExpression``` to check
/// @return ```UTIL_TRUE``` or ```UTIL_FALSE```
int isList(SExpression *exp);

/// @brief Checks if an ```SExpression``` is ```nil``` (```NULL```)
/// @param exp The ```SExpression``` to check
/// @return ```UTIL_TRUE``` or ```UTIL_FALSE```
int isNil(SExpression *exp);

/// @brief Checks if an ```SExpression``` is an ```Atom``` of type ```float``` or ```int```
/// @param exp The ```SExpression``` to check
/// @return ```UTIL_TRUE``` or ```UTIL_FALSE```
int isNumber(SExpression *exp);

/// @brief Checks if an ```SExpression``` is an ```Atom``` of type ```char*```
/// @param exp The ```SExpression``` to check
/// @return ```UTIL_TRUE``` or ```UTIL_FALSE```
int isString(SExpression *exp);

/// @brief Returns the opposite of ```isNil()```
/// @param exp The ```SExpression``` to check
/// @return ```UTIL_TRUE``` or ```UTIL_FALSE```
int toBool(SExpression *exp);

/// @brief Prints an ```SExpression```
/// @param exp The ```SExpression``` to print
void print(SExpression *exp);

#endif
