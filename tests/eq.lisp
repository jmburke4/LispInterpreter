(eq 1 1) ; -> true
(eq 1 2) ; -> ()
(eq 1234567890 1234567890) ; -> true

(eq 1.0 1.0) ; -> true
(eq 1.0 2.0) ; -> ()
(eq 1.1 1.1) ; -> true
(eq 1.1234567890 1.1234567890) ; -> true

(eq (true) true) ; -> true
(eq (true) ()) ; -> ()
(eq () true) ; -> ()
(eq () ()) ; -> ()
(eq (not ()) (not ())) ; -> true
(eq (not (true)) (not (true))) ; -> true

(not (true)) ; -> ()
(not ()) ; -> true
