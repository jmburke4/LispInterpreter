(cons 'a '(b c)) ; Basic single quote distribution
(cons 'a '(b c))
(cons 'a '(b c))
; Do comments work?
; Yes, yes they do.
(cons 'a '(b c ))
(cons 'a '(b c ))
(cons 'a '(b c ))

; Spaces should work too

(cons '(a b) 'c)
(cons '(a b) 'c)
(cons '(a b) 'c)

(cons '(a b ) 'c)
(cons '(a b ) 'c)
(cons '(a b ) 'c)

(cons 'a '())
(cons 'a '())
(cons 'a '())

(cons 12 '(12 34))
(cons 12 '(12 34))
(cons 12 '(12 34))

(cons '(12 34) 56)
(cons '(12 34) 56)
(cons '(12 34) 56)

(cons 12.34 '(56.7 8.9))
(cons 12.34 '(56.7 8.9))
(cons 12.34 '(56.7 8.9))

(cons 'hello '(there general) 'kenobi)
(cons 'hello '(there general) 'kenobi)
(cons 'hello '(there general) 'kenobi)
