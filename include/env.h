#include "types.h"

#ifndef ENV_H
#define ENV_H

/// @brief Deep copies an ```SExpression``` for storage in an ```Environment```
/// @param exp The ```SExpression``` to copy
/// @return A pointer to the new ```SExpression```
SExpression *copyExp(SExpression *exp);

/// @brief Defines a function and stores it in the ```Environment``` stack
/// @param env The ```Environment``` to store the function definition in
/// @param exp The ```SExpression``` holding the function definition
/// @return An ```SExpression``` that is an ```Atom``` with the value ```true```
SExpression *define(Environment *env, SExpression *exp);

/// @brief Allocates space for the global ```Environment```
/// @return A pointer to the new ```Environment```
Environment *initEnvironment();

/// @brief Allocates and iniatilizes a new ```Environment``` for use within the scope of a function
/// @param previous A pointer to the previous ```Environment``` stack
/// @return A pointer to the new ```Environment``` struct
Environment *localEnvironment(Environment* previous);

/// @brief Searches the ```Environment``` for a ```Variable```
/// @param environment The ```Environment``` to look in
/// @param name The name of the ```Variable``` to look for
/// @return A ```Variable``` with an ```SExpression``` member that can be ```nil```
/// @note If the ```Variable``` is not found, lookup will silently return a ```Variable``` with ```nil```
Variable *lookup(Environment *environment, char *name);

/// @brief Allocates space and deep copies the name and ```SExpression```
/// @param name The name of the ```Variable```
/// @param type The enum to determine if a ```Variable``` represents a variable or a function definition
/// @param exp The ```SExpression``` value of the ```Variable``` or the definition of a user-defined function
/// @param params The ```SExpression``` representation of a function definiton's parameters
/// @return A pointer to a ```Variable``` with the deep copied values
Variable *newVariable(char* name, int type, SExpression *exp, SExpression *params);

/// @brief Creates a new variable and stores a pointer to it in the ```Environment```
/// @param environment The ```Environment``` to store the new ```Variable``` in
/// @param name The name of the ```Variable```
/// @param exp The ```SExpression``` value of the ```Variable```
/// @return A pointer to the ```SExpression``` value of the ```Variable```
SExpression *set(Environment *environment, char* name, SExpression *exp);

#endif
