# Lisp Interpreter in C - Jackson Burke, Fall 2025 #

*Please note that VSCode has a built-in markdown previewer/renderer that does not require any extensions. You may preview a markdown file by secondary clicking the filename within VSCode and selecting "Open Preview".*

## Introduction ##

This *README.md* contains information on the repository structure of my project as well as instructions for building and running the project, and a list of known bugs and limitations. Please see *Testing.md* for the testing I have done for Sprint 1.

## Repository Structure ##

#### LispInterpreter ####
- .gitignore
- Makefile *- run* ```make``` *to compile and link into an executable or* ```make clean``` *to remove the bin directory*
- README.md *- this file*
- Testing.md *- the description of my testing of Sprint 1 functionality*
- /.vscode
    - launch.json *- for debugger*
    - settings.json *- IDE settings*
    - tasks.json *- for debugger*
- /include
    - lexer.h *- lexing related types and function signatures*
    - parser.h *- parsing related types and function signatures*
    - util.h *- utility types and function signatures*
- /src
    - lexer.c *- lexing related function definitions*
    - main.c *- the main entry point of the program*
    - parser.c *- parsing related function definitions*
    - util.c *- utility related function definitions*
- /tests
    - s1a.txt *-* ```(cons 'a '(b c))```
    - s1b.txt *-* ```(cons 'a '())```
    - s1c.txt *-* ```(cons 12 '(12 34))```
    - s1d.txt *-* ```(cons 12.34 '(56.7 8.9))```
    - s1e.txt *-* ```(cons 'hello '(there general) 'kenobi)```

## To Run ##

0. This project has been developed and tested with the gcc compiler in a Bash shell using Cygwin64 on Windows.

1. Navigate to the root directory of the repository (*LispInterpreter*) and run ```make``` to compile the header and source code files and link them into the executable (*a.exe*), this outputs everything into *LispInterpreter/bin*. This recursively copies the *tests* directory into the bin folder if the folder does not already exist; if you edit or update files in *LispInterpreter/tests* you must run ```make clean``` and then ```make``` for */bin/tests/* to be updated.  

2. Can run */bin/a.exe* with no arguments and it will run the default text file (currently */bin/tests/s1a.txt*). Can run */bin/a.exe* with one argument that is a relative or absolute filepath to a text file you would like it to process. The program currently only processes the top line of the text file. You may edit the line in */bin/tests/s1a.txt* to pass your own lisp expressions to the interpeter, or you can create a new text file with your lisp expressions and run the interpreter with the filepath to your new file as a command line argument. See *Testing.md* for examples of passing a path to the program from the command line.

## The S-Expression Struct ##

In */include/parser.h* I have defined the following enum and struct: 

```c
typedef enum { ATOM, CONS } SExprType;

typedef struct SExpression {
    SExprType type;
    union {
        char* atom;
        struct {
            struct SExpression* car;
            struct SExpression* cdr;
        } cons;
    };
} SExpression;
```

```SExprType``` is an enum that is used to describe the type of an SExpression, either an atom or a cons cell. This is used in the ```type``` field of the ```SExpression``` struct. The other value in the struct is a C union where either the field ```char* atom``` is used to hold the value if the S-Expression is an atom, or the ```cons``` struct is used to hold two pointers (```car``` and ```cdr```) to two other S-Expression structs if it is a cons cell.

## Known Issues / Limitations ##

In no particular order:

- File processing only works for the top line of a text file
- No working REPL
- Memory leak/pointer issue somewhere (in *lexer.c*?) that requires each token to be printed via ```lexer_printTokens()``` in order for the parser to work properly
- A preceding space is printed before each element, such as after an open parentheses is printed, or when there is a ```nil``` that is not printed to the output
- There is a 256 character limit (255 plus the ```\0``` terminator) imposed by ```util_readFile()``` in */src/util.c*. This means the interpreter can only read lisp expressions that are 255 characters or shorter.
- No automation for running tests
