; Testing for Sprint 5

; I will test the Equality operators first then use them for
; simplifying the testing of the mathematical operators later
; () denotes false
; true denotes true



; EQ

(eq 1 1) ; -> true
(eq 1 2) ; -> ()
(eq 1234567890 1234567890) ; -> true

(eq 1.0 1.0) ; -> true
(eq 1.0 2.0) ; -> ()
(eq 1.1 1.1) ; -> true
(eq 1.1234567890 1.1234567890) ; -> true

; Please note that the types of the atoms being compared must be the same
; (identifiers, strings, integers, floating-point numbers)

(eq 1 1.0) ; -> ()
(eq 1.0 1) ; -> ()
(eq 1 ()) ; -> ()
(eq () ()) ; -> true
(eq true true) ; -> true
(eq true ()) ; -> ()
(eq () true) ; -> ()
; (eq "abc" "abc") ; -> true ; Strings not supported yet
; (eq x x) ; -> true ; Comparing nils not supported yet



; NEQ

(neq 1 1) ; -> ()
(neq 1 2) ; -> true
(neq 1234567890 1234567890) ; -> ()

(neq 1.0 1.0) ; -> ()
(neq 1.0 2.0) ; -> true
(neq 1.1 1.1) ; -> ()
(neq 1.1234567890 1.1234567890) ; -> ()

(neq 1 1.0) ; -> true
(neq 1.0 1) ; -> true
(neq 1 ()) ; -> true
(neq () ()) ; -> ()
; (neq "abc" "abc") ; -> () ; Strings not supported yet
; (neq x x) ; -> () ; Comparing nils not supported yet



; LT



; LTE



; GT



; GTE



; I will use (eq) to test the remaining functions
; All tests should evaluate to true



; Addition

(eq 3 (+ 1 2))
(eq 3.0 (+ 1.0 2.0))
(eq 3.0 (+ 1.0 2))
(eq 3.0 (+ 1 2.0))

(eq -1 (+ 1 -2))
(eq -1.0 (+ 1.0 -2.0))
(eq -1.0 (+ 1.0 -2))
(eq -1.0 (+ 1 -2.0))

(eq 1 (+ -1 2))
(eq 1.0 (+ -1.0 2.0))
(eq 1.0 (+ -1.0 2))
(eq 1.0 (+ -1 2.0))

(eq 579 (+ 123 456))
(eq 6 (+ 1 (+ 2 3)))
(eq 6 (+ (+ 1 2) 3))


; Subtraction

(eq -1 (- 1 2))
(eq -1.0 (- 1.0 2.0))
(eq -1.0 (- 1.0 2))
(eq -1.0 (- 1 2.0))

(eq 3 (- 1 -2))
(eq 3.0 (- 1.0 -2.0))
(eq 3.0 (- 1.0 -2))
(eq 3.0 (- 1 -2.0))

(eq -3 (- -1 2))
(eq -3.0 (- -1.0 2.0))
(eq -3.0 (- -1.0 2))
(eq -3.0 (- -1 2.0))

(eq -333 (- 123 456))
(eq 2 (- 1 (- 2 3)))
(eq -4 (- (- 1 2) 3))



; Multiplication

(eq 2 (* 1 2))
(eq 2.0 (* 1.0 2.0))
(eq 2.0 (* 1.0 2))
(eq 2.0 (* 1 2.0))

(eq -2 (* 1 -2))
(eq -2.0 (* 1.0 -2.0))
(eq -2.0 (* 1.0 -2))
(eq -2.0 (* 1 -2.0))

(eq -2 (* -1 2))
(eq -2.0 (* -1.0 2.0))
(eq -2.0 (* -1.0 2))
(eq -2.0 (* -1 2.0))

(eq 56088 (* 123 456))
(eq 6 (* 1 (* 2 3)))
(eq 6 (* (* 1 2) 3))



; Division

(eq 0 (/ 1 2))
(eq 0.5 (/ 1.0 2.0))
(eq 0.5 (/ 1.0 2))
(eq 0.5 (/ 1 2.0))
(eq () (/ 3 0))
(eq () (/ 3.0 0))

(eq 0 (/ 1 -2))
(eq -0.5 (/ 1.0 -2.0))
(eq -0.5 (/ 1.0 -2))
(eq -0.5 (/ 1 -2.0))

(eq 0 (/ -1 2))
(eq -0.5 (/ -1.0 2.0))
(eq -2.0 (/ -4.0 2))
(eq -2.0 (/ -4 2.0))

(eq 3 (/ 456 123))
(eq 3 (/ 9 (/ 9 3)))
(eq 1 (/ (/ 15 3) 5))

(eq 3.707 (/ 456 123.0)) ; Not sure how rounding will be handled
(eq 3.0 (/ 9 (/ 9 3.0)))
(eq 1.0 (/ (/ 15.0 3) 5))



; Modulo

; Please note that this method only supports two integers

(eq 2 (% 12 5))
(eq 0 (% 10 5))
(eq 455 (% 6515 1515))
(eq () (% 1.0 1))



; Set / Lookup

(eq 4 (set a 4))
(eq 4 (a))
(eq 4 a)
(eq a 4)
(eq 7 (set a 7))
(eq 7 (a))
(eq 7 a)
(eq a 7)
(eq 10 (+ a 3))
(eq (+ 3 a) 10)
(eq 21 (* a 3))
(eq (* 3 a) 21)

(eq 4.0 (set a 4.0))
(eq 4.0 (a))
(eq 4.0 a)
(eq a 4.0)
(eq 7.0 (set a 7.0))
(eq 7.0 (a))
(eq 7.0 a)
(eq a 7.0)
(eq 10.0 (+ a 3.0))
(eq (+ 3.0 a) 10.0)
(eq 21.0 (* a 3.0))
(eq (* 3.0 a) 21.0)
