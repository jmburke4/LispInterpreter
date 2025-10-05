#include "types.h"

#ifndef SEXPR_H
#define SEXPR_H

/// @brief Returns the numerical sum of the values held in the atoms of the passed cons cell
/// @param exp Must be a cons cell with two atoms and no nil terminator
/// @return An ```SExpression``` that is an ```Atom``` of type ```A_FLT``` or ```A_INT```
SExpression *add(SExpression *exp);

/// @brief If ```car(exp)``` and ```cdr(exp)```
/// @param exp The cons cell to evaluate
/// @param env The environment to evaluate the expression in
/// @return ```()``` or ```true```
SExpression *and(SExpression *exp, Environment *env);

/// @brief Initializes an Atom struct
/// @param type The type of Atom to initialize
/// @param val A pointer to a C-String that will be casted to the correct data value
/// @return The pointer to the new Atom struct
SExpression *atom(AtomType type, char *val);

/// @brief Returns the first element in a list
/// @param exp The List to return an element from
/// @return A pointer to an ```SExpression```
SExpression *car(SExpression *exp);

/// @brief Returns the rest of the elements in a list
/// @param exp The List to return elements from
/// @return A pointer to an ```SExpression```
SExpression *cdr(SExpression *exp);

/// @brief Returns the second element in a list
/// @param exp The List to return an element from
/// @return A pointer to an ```SExpression```
SExpression *cadr(SExpression *exp);

/// @brief Returns the third element in a list
/// @param exp The List to return an element from
/// @return A pointer to an ```SExpression```
SExpression *caddr(SExpression *exp);

/// @brief Creates a cons cell with two ```SExpression```s
/// @param car A pointer to the car ```SExpression```
/// @param cdr A pointer to the cdr ```SExpression```
/// @return A pointer to a new ```SExpression```
SExpression *cons(SExpression* car, SExpression* cdr);

/// @brief Returns the quotient of the car divided by the cdr
/// @param exp Must be a cons cell with two atoms and no nil terminator
/// @return An ```SExpression``` that is an ```Atom``` of type ```A_FLT``` or ```A_INT```
/// @note Divide by zero errors are suppressed and return ```nil``` (```NULL```)
SExpression *divide(SExpression *exp);

/// @brief Checks if the car and cdr of a cons cell are equal to each other in value
/// @param exp Must be a cons cell with two atoms and no nil terminator
/// @return ```TRUE``` or ```nil``` (```NULL```)
/// @note If the types of the car and cdr do not match, will silently return ```nil``` (```NULL```)
SExpression *eq(SExpression *exp);

/// @brief Recursively evaluates an ```SExpression```
/// @param exp The ```SExpression``` to evaluate
/// @param env A pointer to the ```Environment``` to evaluate in
/// @return An updated pointer to the ```SExpression``` that was passed as a parameter
SExpression *eval(SExpression *exp, Environment *env);

/// @brief Checks if the car is greater than the cdr
/// @param exp Must be a cons cell with two atoms and no nil terminator
/// @return ```nil``` (```NULL```) or an ```Atom``` of type ```A_ID``` with the value ```true```
SExpression *gt(SExpression *exp);

/// @brief Checks if the car is greater than or equal to the cdr
/// @param exp Must be a cons cell with two atoms and no nil terminator
/// @return ```nil``` (```NULL```) or an ```Atom``` of type ```A_ID``` with the value ```true```
SExpression *gte(SExpression *exp);

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

/// @brief Checks if the car is less than the cdr
/// @param exp Must be a cons cell with two atoms and no nil terminator
/// @return ```nil``` (```NULL```) or an ```Atom``` of type ```A_ID``` with the value ```true```
SExpression *lt(SExpression *exp);

/// @brief Checks if the car is less than or equal to the cdr
/// @param exp Must be a cons cell with two atoms and no nil terminator
/// @return ```nil``` (```NULL```) or an ```Atom``` of type ```A_ID``` with the value ```true```
SExpression *lte(SExpression *exp);

/// @brief Returns the remainder of the car divided by the cdr
/// @param exp Must be a cons cell with two atoms and no nil terminator
/// @return An ```SExpression``` that is an ```Atom``` of type ```A_FLT``` or ```A_INT```
/// @note Divide by zero errors are suppressed and return ```nil``` (```NULL```)
/// @note Only supports two ```int```s, and will return ```nil``` (```NULL```) if passed a ```float```
SExpression *modulo(SExpression *exp);

/// @brief Returns the numerical product of the atoms in the car and cdr
/// @param exp Must be a cons cell with two atoms and no nil terminator
/// @return An ```SExpression``` that is an ```Atom``` of type ```A_FLT``` or ```A_INT```
SExpression *multiply(SExpression *exp);

/// @brief If exp is ```NULL```, return an ```Atom``` of type ```A_ID``` with the string ```true```, else return ```NULL```
/// @param exp The ```SExpression``` to negate
SExpression *not(SExpression *exp);

/// @brief If ```car(exp)``` or ```cdr(exp)```
/// @param exp The cons cell to evaluate
/// @param env The environment to evaluate the expression in
/// @return ```()``` or ```true```
SExpression *or(SExpression *exp, Environment *env);

/// @brief Returns the numerical difference between the atoms in the car and cdr
/// @param exp Must be a cons cell with two atoms and no nil terminator
/// @return An ```SExpression``` that is an ```Atom``` of type ```A_FLT``` or ```A_INT```
SExpression *subtract(SExpression *exp);

/// @brief Returns the opposite of ```isNil()```
/// @param exp The ```SExpression``` to check
/// @return ```UTIL_TRUE``` or ```UTIL_FALSE```
int toBool(SExpression *exp);

/// @brief Prints an ```SExpression```
/// @param exp The ```SExpression``` to print
void print(SExpression *exp);

#endif
