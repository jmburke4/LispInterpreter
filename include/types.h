#ifndef TYPES_H
#define TYPES_H

#define UTIL_SUCCESS 0
#define UTIL_FAILURE -1

#define UTIL_TRUE 1
#define UTIL_FALSE 0 

/// A constant used for declaring string buffers
#define MAX_WORD_LENGTH 24

/// @brief Enums used to determine a type of ```Token```
typedef enum {
    OPEN_PAREN, CLOSE_PAREN,
    
    MINUS, PLUS, SLASH, STAR, MOD,
    
    SINGLE_QUOTE, DOUBLE_QUOTE, DOT, NIL,
    
    NOT, NOTEQ,
    EQ, EQEQ,
    GT, GTE,
    LT, LTE,

    STRING, INT, FLOAT
} TokenType;

/// @brief Represents a token lexed from input
typedef struct {
    /// @brief The string value of the token
    char *val;
    /// @brief The ```TokenType``` enum of the ```Token```
    TokenType type;
    /// @brief A pointer to the previous ```Token```
    struct Token *prev;
    /// @brief A pointer to the next ```Token```
    struct Token *next;
} Token;

/// @brief Holds metadata about a linked list of ```Token```
typedef struct {
    /// @brief The number of ```Token``` in the list
    int size;
    /// @brief The number of Opening Parentheses in the list
    int oparen;
    /// @brief The number of Closing Parentheses in the list
    int cparen;
    /// @brief A pointer to the first ```Token``` in the list
    Token *first;
    /// @brief A pointer to the last ```Token``` in the list
    Token *last;
} TokenList;

/// @brief Returns a pointer to an ```SExpression``` with the string value ```TRUE```
#define TRUE atom(A_ID, "true")

/// @brief An enum for the type of an ```SExpression```
typedef enum { ATOM, CONS } SExprType;

/// @brief An enum for the type of an ```Atom```
typedef enum { A_ID, A_STR, A_INT, A_FLT } AtomType;

/// @brief A struct representing an Atom in Lisp
typedef struct {
    /// @brief An enum tracking the data type of the ```Atom```
    AtomType type;
    union {
        char *strVal;
        int intVal;
        float floatVal;
    };
} Atom;

/// @brief A struct representing an S-Expression in Lisp
typedef struct SExpression {
    /// @brief An enum to track whether an ```SExpression``` is an ```Atom``` or ```Cons``` cell
    SExprType type;
    union {
        /// @brief Holds numbers, symbols, and strings
        Atom atom;
        /// @brief Holds pointers to other ```SExpression``` structs
        struct {
            /// @brief A pointer to the car of the ```Cons``` cell
            struct SExpression *car;
            /// @brief A pointer to the cdr of the ```Cons``` cell
            struct SExpression *cdr;
        } cons;
    };
} SExpression;

/// @brief This represents a variable held in the environment
typedef struct {
    /// @brief An enum to track whether a ```Variable``` represents just a variable object or a function definition
    enum { VAR, FUNC } type;
    /// @brief The c-string to lookup the ```Variable``` by
    char* name;
    /// @brief The ```SExpression``` value of the variable
    SExpression *exp;
    /// @brief An ```SExpression``` representing the parameters for a function
    SExpression *param;
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

#endif
