
; And

(and (true) (true))
(and () ()) ; -> ()
(and () (true)) ; -> ()
(and (true) ()) ; -> ()
(and (eq 1 1) (eq 2 2))
(and 1 2)
(not (and (not (eq 1 1)) (not (eq 2 2))))
(eq () (and () ()))
(set a (true))
(a)
(and (a) (a))
(eq (set a ()) ())
(and (a) (a)) ; -> ()
(set b (true))
(eq (and (a) (b)) ())
(eq () (and () (set c 3))) ; the eval of (set c 3) should not happen because and () short circuits
(c) ; -> ()
(eq (c) ())

; Or

(or (true) (true))
(or () true)
(or () ()) ; -> ()
(or (eq 1 1) (eq 2 2))
(eq (or (not (eq 1 1)) (not (eq 2 2)) ) ())
(eq (or () ()) ())
(set a (true))
(or (a) (a))
(eq (set a ()) ())
(eq () (or (a) (a)))
(set b (true))
(eq (or (a) (b)) (true))

