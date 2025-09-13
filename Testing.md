# Lisp Interpreter in C - Jackson Burke, Fall 2025 - Testing #

## Introduction ##

My interpreter currently only takes input via reading the top line of a *.txt* file. I have saved the following files with the tests I have been working with for Sprint 1. All commands entered below are run in the root directory of the project (*LispInterpreter/*).

## Tests ##

### s1a.txt ###

```lisp
(cons 'a '(b c))
```

Running ```$ ./bin/a ./bin/tests/s1a.txt``` returns ```( a b c)```

### s1b.txt ###

```lisp
(cons 'a '())
```

Running ```$ ./bin/a ./bin/tests/s1b.txt``` returns ```( a )```

### s1c.txt ###

```lisp
(cons 12 '(12 34))
```

Running ```$ ./bin/a ./bin/tests/s1c.txt``` returns ```( 12 12 34)```

### s1d.txt ###

```lisp
(cons 12.34 '(56.7 8.9))
```

Running ```$ ./bin/a ./bin/tests/s1d.txt``` returns ```( 12.34 56.7 8.9)```

### s1e.txt ###

```lisp
(cons 'hello '(there general) 'kenobi)
```

Running ```$ ./bin/a ./bin/tests/s1e.txt``` returns ```( hello there general kenobi)```
