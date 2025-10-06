# Lisp Interpreter in C - Jackson Burke, Fall 2025 - Testing #

## Introduction ##

Most of the tests are set up to use eq() or neq() to make the expression return ```true```, regardless of the type of input. Below is the output of running each of the test files. When applicable, please see comments following the ```;``` symbol. If the expected output of the test is not ```true```, the expected output will be noted in the comment for that line. Some tests that fail are still included with an error message or comment with a note about that specific test. The line following ```>``` is the lisp line read from file, with the output printed immediately below it.

## Tests ##

### andor.lisp ###
For testing ```(and)``` and ```(or)```.

```lisp
$ ./bin/a ./bin/tests/andor.lisp

>(and (true) (true))
true

>(and () ()) ; -> ()
()

>(and () (true)) ; -> ()
()

>(and (true) ()) ; -> ()
()

>(and (eq 1 1) (eq 2 2))
true

>(and 1 2)
true

>(not (and (not (eq 1 1)) (not (eq 2 2))))
true

>(eq () (and () ()))
true

>(set a (true))
true

>(a)
true

>(and (a) (a))
true

>(eq (set a ()) ())
true

>(and (a) (a)) ; -> ()
()

>(set b (true))
true

>(eq (and (a) (b)) ())
true

>(eq () (and () (set c 3))) ; the eval of (set c 3) should not happen because and () short circuits
true

>(c) ; -> ()
()

>(eq (c) ())
true

>(or (true) (true))
true

>(or () true)
true

>(or () ()) ; -> ()
()

>(or (eq 1 1) (eq 2 2))
true

>(eq (or (not (eq 1 1)) (not (eq 2 2)) ) ())
true

>(eq (or () ()) ())
true

>(set a (true))
true

>(or (a) (a))
true

>(eq (set a ()) ())
true

>(eq () (or (a) (a)))
true

>(set b (true))
true

>(eq (or (a) (b)) (true))
true
```

### eq.lisp ###
For testing ```(eq)``` and ```(neq)```.

```lisp
$ ./bin/a ./bin/tests/eq.lisp

>(eq 1 1)
true

>(eq 1 2) ; -> ()
()

>(eq 1234567890 1234567890)
true

>(eq 1.0 1.0)
true

>(eq 1.0 2.0) ; -> ()
()

>(eq 1.1 1.1)
true

>(eq 1.1234567890 1.1234567890)
true

>(eq (true) true)
true

>(eq (true) ()) ; -> ()
()

>(eq () true) ; -> ()
()

>(eq () ())
true

>(eq (not ()) (not ()))
true

>(eq (not (true)) (not (true)))
true

>(not (true)) ; -> ()
()

>(not ())
true
```

### func.lisp ###
For testing ```(declare)``` and ```(lambda)```. Please note that functions like ```(set)``` return the evaluated value upon success, or ```nil``` on failure.

```lisp
$ ./bin/a ./bin/tests/func.lisp

>(set rectLength 4) ; -> 4
4

>(set rectWidth 6) ; -> 6
6

>(define area (height width) (* height width))
true

>(set rectArea (area rectLength rectWidth)) ; -> 24
24

>(rectArea) ; -> 24
24

>(set x 4) ; -> 4
4

>(set y 5) ; -> 5
5

>(set z 6) ; -> 6
6

>(define square (x) (* x x))
true

>(square x) ; -> 16
16

>(square y) ; -> 25
25

>(square z) ; -> 36
36

>(square (square 2)) ; -> 16
16

>(* 2 (square 3)) ; -> 18
18

>(define volume (height length width) (* height (* width length)))
true

>(volume 2 3 4) ; -> 24
24

>((lambda (x) (x)) 3) ; -> 3
3

>((lambda (x y) (+ x y)) 2 4) ; -> 6
6

>((lambda (x y z) (* x (* y z))) 2 3 4) ; -> 24
24

>(define cube (x) ((lambda (a) (* a ( * a a))) x)) ; -> true
true

>(cube 3) ; -> 27
27
```

### ifcond.lisp ###
For testing ```(if)``` and ```(cond)```. The interpreter does not allow for processing multiple lines at once, so cond statements must be all one line.

```lisp
$ ./bin/a ./bin/tests/ifcond.lisp

>(eq -1 (cond (eq 1 0) (set a 1) (eq 0 1) (set a 2) (true) (set a -1)))
true

>(eq -1 (a))
true

>(eq 1 (cond (true) (set a 1) (eq 0 1) (set a 2) (true) (set a -1)))
true

>(eq 1 (a))
true

>(eq 2 (cond (eq 1 0) (set a 1) (true) (set a 2) (true) (set a -1)))
true

>(eq 2 (a))
true

>(eq 1 (if (true) (set a 1) (set a 0)))
true

>(eq 1 a)
true

>(eq 0 (if () (set a 1) (set a 0)))
true

>(eq 0 a)
true

>(eq 3 (if (gt 3 2) (set a 3) (set a 2)))
true

>(eq 3 a)
true

>(eq 10 (if (lt (a) 10) (set a 10) ()))
true

>(eq 10 a)
true

>(eq () (if (lt (a) 9) (set a 9) ()))
true

>(eq 10 a)
true
```

### master.lisp ###
A catch all for testing math operators, comparison operators, etc.

```lisp
$ ./bin/a ./bin/tests/master.lisp

>(eq 1 1)
true

>(eq 1 2) ; -> ()
()

>(eq 1234567890 1234567890)
true

>(eq 1.0 1.0)
true

>(eq 1.0 2.0) ; -> ()
()

>(eq 1.1 1.1)
true

>(eq 1.1234567890 1.1234567890)
true

>(eq (true) true)
true

>(eq (true) ()) ; -> ()
()

>(eq () true) ; -> ()
()

>(eq () ())
true

>(eq (not ()) (not ()))
true

>(eq (not (true)) (not (true)))
true

>(not (true)) ; -> ()
()

>(not ())
true

>(eq 1 1.0) ; -> ()
()

>(eq 1.0 1) ; -> ()
()

>(eq 1 ()) ; -> ()
()

>(eq () ())
true

>(eq (true) true)
true

>(eq (true) ()) ; -> ()
()

>(eq () true) ; -> ()
()

>(set x 3) ; -> 3
3

>(eq (x) x)
true

>(neq 1 1) ; -> ()
()

>(neq 1 2)
true

>(neq 1234567890 1234567890) ; -> ()
()

>(neq 1.0 1.0) ; -> ()
()

>(neq 1.0 2.0)
true

>(neq 1.1 1.1) ; -> ()
()

>(neq 1.1234567890 1.1234567890) ; -> ()
()

>(neq 1 1.0)
true

>(neq 1.0 1)
true

>(neq 1 ())
true

>(neq () ()) ; -> ()
()

>(neq x x) ; -> ()
()

>(eq (true) (lt 3 4))
true

>(eq () (lt 4 4))
true

>(eq () (lt 5 4))
true

>(eq () (lt 3 -4))
true

>(eq () (lt -4 -4))
true

>(eq (true) (lt -5 -4))
true

>(eq (true) (lt 3.0 4.0))
true

>(eq () (lt 4.0 4.0))
true

>(eq () (lt 5.0 4.0))
true

>(eq () (lt 3.0 -4.0))
true

>(eq () (lt -4.0 -4.0))
true

>(eq (true) (lt -5.0 -4.0))
true

>(eq (true) (lt 3.0 4))
true

>(eq () (lt 4.0 4))
true

>(eq () (lt 5.0 4))
true

>(eq () (lt 3.0 -4))
true

>(eq () (lt -4.0 -4))
true

>(eq (true) (lt -5.0 -4))
true

>(eq (true) (lt 3 4.0))
true

>(eq () (lt 4 4.0))
true

>(eq () (lt 5 4.0))
true

>(eq () (lt 3 -4.0))
true

>(eq () (lt -4 -4.0))
true

>(eq (true) (lt -5 -4.0))
true

>(eq (true) (lte 3 4))
true

>(eq (true) (lte 4 4))
true

>(eq () (lte 5 4))
true

>(eq () (lte 3 -4))
true

>(eq (true) (lte -4 -4))
true

>(eq (true) (lte -5 -4))
true

>(eq (true) (lte 3.0 4.0))
true

>(eq (true) (lte 4.0 4.0))
true

>(eq () (lte 5.0 4.0))
true

>(eq () (lte 3.0 -4.0))
true

>(eq (true) (lte -4.0 -4.0))
true

>(eq (true) (lte -5.0 -4.0))
true

>(eq (true) (lte 3.0 4))
true

>(eq (true) (lte 4.0 4))
true

>(eq () (lte 5.0 4))
true

>(eq () (lte 3.0 -4))
true

>(eq (true) (lte -4.0 -4))
true

>(eq (true) (lte -5.0 -4))
true

>(eq (true) (lte 3 4.0))
true

>(eq (true) (lte 4 4.0))
true

>(eq () (lte 5 4.0))
true

>(eq () (lte 3 -4.0))
true

>(eq (true) (lte -4 -4.0))
true

>(eq (true) (lte -5 -4.0))
true

>(eq () (gt 3 4))
true

>(eq () (gt 4 4))
true

>(eq (true) (gt 5 4))
true

>(eq (true) (gt 3 -4))
true

>(eq () (gt -4 -4))
true

>(eq () (gt -5 -4))
true

>(eq () (gt 3.0 4.0))
true

>(eq () (gt 4.0 4.0))
true

>(eq (true) (gt 5.0 4.0))
true

>(eq (true) (gt 3.0 -4.0))
true

>(eq () (gt -4.0 -4.0))
true

>(eq () (gt -5.0 -4.0))
true

>(eq () (gt 3.0 4))
true

>(eq () (gt 4.0 4))
true

>(eq (true) (gt 5.0 4))
true

>(eq (true) (gt 3.0 -4))
true

>(eq () (gt -4.0 -4))
true

>(eq () (gt -5.0 -4))
true

>(eq () (gt 3 4.0))
true

>(eq () (gt 4 4.0))
true

>(eq (true) (gt 5 4.0))
true

>(eq (true) (gt 3 -4.0))
true

>(eq () (gt -4 -4.0))
true

>(eq () (gt -5 -4.0))
true

>(eq () (gte 3 4))
true

>(eq (true) (gte 4 4))
true

>(eq (true) (gte 5 4))
true

>(eq (true) (gte 3 -4))
true

>(eq (true) (gte -4 -4))
true

>(eq () (gte -5 -4))
true

>(eq () (gte 3.0 4.0))
true

>(eq (true) (gte 4.0 4.0))
true

>(eq (true) (gte 5.0 4.0))
true

>(eq (true) (gte 3.0 -4.0))
true

>(eq (true) (gte -4.0 -4.0))
true

>(eq () (gte -5.0 -4.0))
true

>(eq () (gte 3.0 4))
true

>(eq (true) (gte 4.0 4))
true

>(eq (true) (gte 5.0 4))
true

>(eq (true) (gte 3.0 -4))
true

>(eq (true) (gte -4.0 -4))
true

>(eq () (gte -5.0 -4))
true

>(eq () (gte 3 4.0))
true

>(eq (true) (gte 4 4.0))
true

>(eq (true) (gte 5 4.0))
true

>(eq (true) (gte 3 -4.0))
true

>(eq (true) (gte -4 -4.0))
true

>(eq () (gte -5 -4.0))
true

>(eq 3 (+ 1 2))
true

>(eq 3.0 (+ 1.0 2.0))
true

>(eq 3.0 (+ 1.0 2))
true

>(eq 3.0 (+ 1 2.0))
true

>(eq -1 (+ 1 -2))
true

>(eq -1.0 (+ 1.0 -2.0))
true

>(eq -1.0 (+ 1.0 -2))
true

>(eq -1.0 (+ 1 -2.0))
true

>(eq 1 (+ -1 2))
true

>(eq 1.0 (+ -1.0 2.0))
true

>(eq 1.0 (+ -1.0 2))
true

>(eq 1.0 (+ -1 2.0))
true

>(eq 579 (+ 123 456))
true

>(eq 6 (+ 1 (+ 2 3)))
true

>(eq 6 (+ (+ 1 2) 3))
true

>(eq -1 (- 1 2))
true

>(eq -1.0 (- 1.0 2.0))
true

>(eq -1.0 (- 1.0 2))
true

>(eq -1.0 (- 1 2.0))
true

>(eq 3 (- 1 -2))
true

>(eq 3.0 (- 1.0 -2.0))
true

>(eq 3.0 (- 1.0 -2))
true

>(eq 3.0 (- 1 -2.0))
true

>(eq -3 (- -1 2))
true

>(eq -3.0 (- -1.0 2.0))
true

>(eq -3.0 (- -1.0 2))
true

>(eq -3.0 (- -1 2.0))
true

>(eq -333 (- 123 456))
true

>(eq 2 (- 1 (- 2 3)))
true

>(eq -4 (- (- 1 2) 3))
true

>(eq 2 (* 1 2))
true

>(eq 2.0 (* 1.0 2.0))
true

>(eq 2.0 (* 1.0 2))
true

>(eq 2.0 (* 1 2.0))
true

>(eq -2 (* 1 -2))
true

>(eq -2.0 (* 1.0 -2.0))
true

>(eq -2.0 (* 1.0 -2))
true

>(eq -2.0 (* 1 -2.0))
true

>(eq -2 (* -1 2))
true

>(eq -2.0 (* -1.0 2.0))
true

>(eq -2.0 (* -1.0 2))
true

>(eq -2.0 (* -1 2.0))
true

>(eq 56088 (* 123 456))
true

>(eq 6 (* 1 (* 2 3)))
true

>(eq 6 (* (* 1 2) 3))
true

>(eq 0 (/ 1 2))
true

>(eq 0.5 (/ 1.0 2.0))
true

>(eq 0.5 (/ 1.0 2))
true

>(eq 0.5 (/ 1 2.0))
true

>(eq () (/ 3 0))
true

>(eq () (/ 3.0 0))
true

>(eq 0 (/ 1 -2))
true

>(eq -0.5 (/ 1.0 -2.0))
true

>(eq -0.5 (/ 1.0 -2))
true

>(eq -0.5 (/ 1 -2.0))
true

>(eq 0 (/ -1 2))
true

>(eq -0.5 (/ -1.0 2.0))
true

>(eq -2.0 (/ -4.0 2))
true

>(eq -2.0 (/ -4 2.0))
true

>(eq 3 (/ 456 123))
true

>(eq 3 (/ 9 (/ 9 3)))
true

>(eq 1 (/ (/ 15 3) 5))
true

>(/ 456 123.0) ; -> ~3.7
3.707317

>(eq 3.0 (/ 9 (/ 9 3.0)))
true

>(eq 1.0 (/ (/ 15.0 3) 5))
true

>(eq 2 (% 12 5))
true

>(eq 0 (% 10 5))
true

>(eq 455 (% 6515 1515))
true

>(eq () (% 1.0 1))
Only integer types are supported for the modulo operation
true

>(eq 4 (set a 4))
true

>(eq 4 (a))
true

>(eq 4 a)
true

>(eq (a) 4)
true

>(eq 7 (set a 7))
true

>(eq 7 (a))
true

>(eq 7 a)
true

>(eq (a) 7)
true

>(eq 10 (+ (a) 3))
true

>(eq (+ 3 a) 10)
true

>(eq 21 (* (a) 3))
true

>(eq (* 3 a) 21)
true

>(eq 4.0 (set a 4.0))
true

>(eq 4.0 (a))
true

>(eq 4.0 a)
true

>(eq (a) 4.0)
true

>(eq 7.0 (set a 7.0))
true

>(eq 7.0 (a))
true

>(eq 7.0 a)
true

>(eq (a) 7.0)
true

>(eq 10.0 (+ (a) 3.0))
true

>(eq (+ 3.0 a) 10.0)
true

>(eq 21.0 (* (a) 3.0))
true

>(eq (* 3.0 a) 21.0)
true

>(set a 3) ; -> 3
3

>('a) ; -> (a)
(a)

>(+ 3 'a) ; -> ()
S-Expression passed to add() must be a dotted pair
()

>(+ 3 a) ; -> 6
6
```
