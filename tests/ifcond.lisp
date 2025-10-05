
; Cond
(eq -1 (cond (eq 1 0) (set a 1) (eq 0 1) (set a 2) (true) (set a -1)))
(eq -1 (a))

(eq 1 (cond (true) (set a 1) (eq 0 1) (set a 2) (true) (set a -1)))
(eq 1 (a))

(eq 2 (cond (eq 1 0) (set a 1) (true) (set a 2) (true) (set a -1)))
(eq 2 (a))

; If
(eq 1 (if (true) (set a 1) (set a 0)))
(eq 1 a)

(eq 0 (if () (set a 1) (set a 0)))
(eq 0 a)

(eq 3 (if (gt 3 2) (set a 3) (set a 2)))
(eq 3 a)

(eq 10 (if (lt (a) 10) (set a 10) ()))
(eq 10 a)

(eq () (if (lt (a) 9) (set a 9) ()))
(eq 10 a)
