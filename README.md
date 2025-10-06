# Lisp Interpreter in C - Jackson Burke, Fall 2025 #

*Please note that VSCode has a built-in markdown previewer/renderer that does not require any extensions. You may preview a markdown file by secondary clicking the filename within VSCode and selecting "Open Preview".*

## Introduction ##

This *README.md* contains information on the repository structure of my project as well as instructions for building and running the project, and a list of known bugs and limitations. Please see *Testing.md* for the testing I have done. 

View on [Github](https://github.com/jmburke4/LispInterpreter).

## Repository Structure ##

#### LispInterpreter ####
- .gitignore
- Makefile *- run* ```make``` *to compile and link into an executable or* ```make clean``` *to remove the bin directory*
- README.md *- this file*
- Testing.md *- the description of my testing of Lisp functionality*
- /.vscode
    - launch.json *- for debugger*
    - settings.json *- IDE settings*
    - tasks.json *- for debugger*
- /include
    - env.h *- Functions related to managing variable and function declarations in different scopes*
    - lexer.h *- lexing related types and function signatures*
    - parser.h *- parsing related types and function signatures*
    - sexpr.h *- The SExpression-related functions and eval*
    - tester.h *- This was used for programmatically building SExpressions before parsing was complete, it is not actively used by by the interpeter other than for development purposes*
    - types.h *- Holds all type definitons including the ```SExpression```*
    - util.h *- utility types and function signatures*
- /src
    - env.c *- Functions related to managing variable and function declarations in different scopes*
    - lexer.c *- lexing related types and function signatures*
    - main.c *- The main entry point of the program, also handles file processing and the REPL*
    - parser.c *- parsing related types and function signatures*
    - sexpr.c *- The SExpression-related functions and eval*
    - tester.c *- This was used for programmatically building SExpressions before parsing was complete, it is not actively used by by the interpeter other than for development purposes*
    - util.c *- utility types and function signatures*
- /tests
    - andor.lisp
    - eq.lisp
    - func.lisp
    - ifcond.lisp
    - master.lisp

## To Run ##

1. This project has been developed and tested with the gcc compiler in a Bash shell using Cygwin64 on Windows.

2. Navigate to the root directory of the repository (*LispInterpreter*) and run ```make``` to compile the header and source code files and link them into the executable (*a.exe*), this outputs everything into *LispInterpreter/bin*. This recursively copies the *tests* directory into the bin folder if the folder does not already exist; if you edit or update files in *LispInterpreter/tests* you must run ```make cpt``` (make copy tests), or alternatively ```make clean``` and then ```make``` for */bin/tests/* to be updated.

3. Can run */bin/a.exe* with no arguments and it will enter the REPL. Can run */bin/a.exe* with one argument that is a relative or absolute filepath to a text file you would like it to process. The interpreter exits on reaching the end of file. See *Testing.md* for examples of passing a path to the program from the command line.

## The S-Expression Struct ##

In */include/types.h* I have defined the following enum and struct: 

```c
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
```

```SExprType``` is an enum that is used to describe the type of an SExpression, either an atom or a cons cell. This is used in the ```type``` field of the ```SExpression``` struct. The other value in the struct is a C union where either the field ```char* atom``` is used to hold the value if the S-Expression is an atom, or the ```cons``` struct is used to hold two pointers (```car``` and ```cdr```) to two other S-Expression structs if it is a cons cell.

## Known Issues / Limitations ##

In order of documented on Github:

There is a 256 character limit (255 plus the \0 terminator) imposed by the file reader in the main method. This means the interpreter can only read lisp expressions that are 255 characters or shorter. It also currently ends scanning when reaching a new line, so all contiguous lisp expressions may only span one line.

Similar to the above issue, there is a maximum word length of 24 characters. This means that strings may only be 21 characters long (2 for the quotes plus 1 for the \0 terminator), numbers and identifiers may only be 21 characters long.

Negative number literals are supported, but the minus sign cannot be used to directly negate the numerical value of a number, although multiply by negative one works.
```lisp
>(set a 3)
3

>(* -1 a)
-3
```

Most Atoms that are printed are printed without surrounding quotation marks. This needs to be updated to print ```(true)``` or ```(1)``` for consistency.

Certain float literals round improperly:
```lisp
>(set a 55.6)
55.599998

>(a)
55.599998
```

If in the REPL, you must be careful to use the backspace key instead of arrowing back and writing over your input or the scanner will be unable to lex the keyboard input.

There are intermittent parsing issues where an ```Atom``` in the ```car``` position of an ```SExpression``` will not evaluate unless it is enclosed in parentheses. I have not been able to narrow down when and when it doesn't happen.
```lisp
>(set a 1)
1

>(+ a 1)
()

>(+ (a) 1)
2
```