; I will test the Equality operators first then use them for
; simplifying the testing of the mathematical operators later
; () denotes false
; true denotes true



; EQ

(eq 1 1)
(eq 1 2) ; -> ()
(eq 1234567890 1234567890)

(eq 1.0 1.0)
(eq 1.0 2.0) ; -> ()
(eq 1.1 1.1)
(eq 1.1234567890 1.1234567890)

(eq (true) true)
(eq (true) ()) ; -> ()
(eq () true) ; -> ()
(eq () ())
(eq (not ()) (not ()))
(eq (not (true)) (not (true)))

(not (true)) ; -> ()
(not ())


; Please note that the types of the atoms being compared must be the same
; (identifiers, strings, integers, floating-point numbers)

(eq 1 1.0) ; -> ()
(eq 1.0 1) ; -> ()
(eq 1 ()) ; -> ()
(eq () ())
(eq (true) true)
(eq (true) ()) ; -> ()
(eq () true) ; -> ()
(set x 3) ; -> 3
(eq (x) x)



; NEQ

(neq 1 1) ; -> ()
(neq 1 2)
(neq 1234567890 1234567890) ; -> ()

(neq 1.0 1.0) ; -> ()
(neq 1.0 2.0)
(neq 1.1 1.1) ; -> ()
(neq 1.1234567890 1.1234567890) ; -> ()

(neq 1 1.0)
(neq 1.0 1)
(neq 1 ())
(neq () ()) ; -> ()
(neq x x) ; -> () 



; LT

(eq (true) (lt 3 4))
(eq () (lt 4 4))
(eq () (lt 5 4))
(eq () (lt 3 -4))
(eq () (lt -4 -4))
(eq (true) (lt -5 -4))

(eq (true) (lt 3.0 4.0))
(eq () (lt 4.0 4.0))
(eq () (lt 5.0 4.0))
(eq () (lt 3.0 -4.0))
(eq () (lt -4.0 -4.0))
(eq (true) (lt -5.0 -4.0))

(eq (true) (lt 3.0 4))
(eq () (lt 4.0 4))
(eq () (lt 5.0 4))
(eq () (lt 3.0 -4))
(eq () (lt -4.0 -4))
(eq (true) (lt -5.0 -4))

(eq (true) (lt 3 4.0))
(eq () (lt 4 4.0))
(eq () (lt 5 4.0))
(eq () (lt 3 -4.0))
(eq () (lt -4 -4.0))
(eq (true) (lt -5 -4.0))



; LTE

(eq (true) (lte 3 4))
(eq (true) (lte 4 4))
(eq () (lte 5 4))
(eq () (lte 3 -4))
(eq (true) (lte -4 -4))
(eq (true) (lte -5 -4))

(eq (true) (lte 3.0 4.0))
(eq (true) (lte 4.0 4.0))
(eq () (lte 5.0 4.0))
(eq () (lte 3.0 -4.0))
(eq (true) (lte -4.0 -4.0))
(eq (true) (lte -5.0 -4.0))

(eq (true) (lte 3.0 4))
(eq (true) (lte 4.0 4))
(eq () (lte 5.0 4))
(eq () (lte 3.0 -4))
(eq (true) (lte -4.0 -4))
(eq (true) (lte -5.0 -4))

(eq (true) (lte 3 4.0))
(eq (true) (lte 4 4.0))
(eq () (lte 5 4.0))
(eq () (lte 3 -4.0))
(eq (true) (lte -4 -4.0))
(eq (true) (lte -5 -4.0))


; GT

(eq () (gt 3 4))
(eq () (gt 4 4))
(eq (true) (gt 5 4))
(eq (true) (gt 3 -4))
(eq () (gt -4 -4))
(eq () (gt -5 -4))

(eq () (gt 3.0 4.0))
(eq () (gt 4.0 4.0))
(eq (true) (gt 5.0 4.0))
(eq (true) (gt 3.0 -4.0))
(eq () (gt -4.0 -4.0))
(eq () (gt -5.0 -4.0))

(eq () (gt 3.0 4))
(eq () (gt 4.0 4))
(eq (true) (gt 5.0 4))
(eq (true) (gt 3.0 -4))
(eq () (gt -4.0 -4))
(eq () (gt -5.0 -4))

(eq () (gt 3 4.0))
(eq () (gt 4 4.0))
(eq (true) (gt 5 4.0))
(eq (true) (gt 3 -4.0))
(eq () (gt -4 -4.0))
(eq () (gt -5 -4.0))



; GTE

(eq () (gte 3 4))
(eq (true) (gte 4 4))
(eq (true) (gte 5 4))
(eq (true) (gte 3 -4))
(eq (true) (gte -4 -4))
(eq () (gte -5 -4))

(eq () (gte 3.0 4.0))
(eq (true) (gte 4.0 4.0))
(eq (true) (gte 5.0 4.0))
(eq (true) (gte 3.0 -4.0))
(eq (true) (gte -4.0 -4.0))
(eq () (gte -5.0 -4.0))

(eq () (gte 3.0 4))
(eq (true) (gte 4.0 4))
(eq (true) (gte 5.0 4))
(eq (true) (gte 3.0 -4))
(eq (true) (gte -4.0 -4))
(eq () (gte -5.0 -4))

(eq () (gte 3 4.0))
(eq (true) (gte 4 4.0))
(eq (true) (gte 5 4.0))
(eq (true) (gte 3 -4.0))
(eq (true) (gte -4 -4.0))
(eq () (gte -5 -4.0))



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

(/ 456 123.0) ; -> ~3.7
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
(eq (a) 4)
(eq 7 (set a 7))
(eq 7 (a))
(eq 7 a)
(eq (a) 7)
(eq 10 (+ (a) 3))
(eq (+ 3 a) 10)
(eq 21 (* (a) 3))
(eq (* 3 a) 21)

(eq 4.0 (set a 4.0))
(eq 4.0 (a))
(eq 4.0 a)
(eq (a) 4.0)
(eq 7.0 (set a 7.0))
(eq 7.0 (a))
(eq 7.0 a)
(eq (a) 7.0)
(eq 10.0 (+ (a) 3.0))
(eq (+ 3.0 a) 10.0)
(eq 21.0 (* (a) 3.0))
(eq (* 3.0 a) 21.0)

; quote

(set a 3) ; -> 3
('a) ; -> (a)
(+ 3 'a) ; -> ()
(+ 3 a) ; -> 6


