#include "sexpr.h"

#ifndef ENV_H
#define ENV_H

/// @brief This represents a variable held in the environment
typedef struct {
    /// @brief The c-string to lookup the ```Variable``` by
    char* name;
    /// @brief The ```SExpression``` value of the variable
    SExpression *exp;
    /// @brief A pointer to the next ```Variable``` on the stack
    struct Variable *next;
} Variable;

/// @brief A stack with each node pointing to a ```Variable```
typedef struct {
    /// @brief A pointer to the ```Variable``` on the top of the stack
    Variable *top;
    /// @brief A pointer to the next ```Environment```
    struct Environment *next;
} Environment;

/// @brief Deep copies an ```SExpression``` for storage in an ```Environment```
/// @param exp The ```SExpression``` to copy
/// @return A pointer to the new ```SExpression```
SExpression *copyExp(SExpression *exp);

/// @brief Allocates space for a new ```Environment```
/// @return A pointer to the new ```Environment```
Environment *initEnvironment();

/// @brief Searches the ```Environment``` for a ```Variable```
/// @param environment The ```Environment``` to look in
/// @param name The name of the ```Variable``` to look for
/// @return A ```Variable``` or ```NULL```
Variable *lookup(Environment *environment, char *name);

/// @brief Allocates space and deep copies the name and ```SExpression```
/// @param name The name of the ```Variable```
/// @param exp The ```SExpression``` value of the ```Variable```
/// @return A pointer to a ```Variable``` with the deep copied values
Variable *newVariable(char* name, SExpression *exp);

/// @brief Creates a new variable and stores a pointer to it in the ```Environment```
/// @param environment The ```Environment``` to store the new ```Variable``` in
/// @param name The name of the ```Variable```
/// @param exp The ```SExpression``` value of the ```Variable```
/// @return A pointer to the ```SExpression``` value of the ```Variable```
SExpression *set(Environment *environment, char* name, SExpression *exp);

#endif
