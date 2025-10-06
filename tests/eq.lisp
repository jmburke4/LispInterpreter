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
