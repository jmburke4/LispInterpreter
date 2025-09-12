need doubly linked list
    - push_back
    - remove
    - search

need bst to hold and lookup list of reserved words

[scanner/lexer](https://craftinginterpreters.com/a-map-of-the-territory.html#scanning)
    parses input into tokens such as " / ( {

[parser](https://craftinginterpreters.com/a-map-of-the-territory.html#parsing)


/* The parser takes tokens, and combines them into an s-expression. 
* An s-expression is either an atom (number, string, symbol) or a list of atoms.
* Ex. (add 1 2) is a list of three s-expressions: the symbol "add", the number 1, and the number 2.
* The parser will build a tree structure representing the s-expression.
* The parser will also handle syntax errors, such as unmatched parentheses.
* The parser will return the root of the s-expression tree.
* The parser will be used by the interpreter to evaluate the s-expression.
*/


