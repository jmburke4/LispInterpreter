#ifndef TYPES_H
#define TYPES_H

#define UTIL_SUCCESS 0
#define UTIL_FAILURE -1

#define UTIL_TRUE 1
#define UTIL_FALSE 0 

#define MAX_WORD_LENGTH 12

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
// Usage: printf(ANSI_COLOR_RED "This text is red." ANSI_COLOR_RESET "\n");

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

typedef struct {
    char *val;
    TokenType type;
    struct Token *prev;
    struct Token *next;
} Token;

typedef struct {
    int size;
    int oparen;
    int cparen;
    Token *first;
    Token *last;
} TokenList;

#define TRUE atom(A_ID, "true")

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

/// @brief This represents a variable held in the environment
typedef struct {
    enum { VAR, FUNC } type;
    /// @brief The c-string to lookup the ```Variable``` by
    char* name;
    /// @brief The ```SExpression``` value of the variable
    SExpression *exp;

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
