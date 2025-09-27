; Testing parentheses normalizations
(a b) ; -> (a b)
(a b c) ; -> (a (b c))
((a b) c) ; -> ((a b) c)
(a (b c)) ; -> (a (b c))

(a b c d) ; -> (a (b (c d)))
(a b c d e) ; -> (a (b (c (d e))))

((a b) c d) ; -> ((a b) (c d))
(a (b c) d) ; -> (a ((b c) d))
(a b (c d)) ; -> (a (b (c d)))

; Testing quote
('a b) ; -> ((quote a) b)
(a 'b) ; -> (a (quote b))
('a 'b) ; -> ((quote a) (quote b))

(a '(b c)) ; -> (a (quote (b c)))
('(a b) c) ; -> ((quote (a b)) c)

('a '(b c)) ; -> ((quote a) (quote (b c)))
('(a b) 'c) ; -> ((quote (a b)) (quote c))

; Testing number handling
(12 34 56) ; -> (12 (34 56))
(1.2 3.4 5.6) ; -> (1.2 (3.4 5.6))
(1 2.3) ; -> (1 2.3)
(1.2 3) ; -> (1.2 3)

; Testing string handling
(ab cd ef) ; -> (ab (cd ef))
(a bd cde fghi) ; -> (a (bd (cde fghi)))
(hello there general kenobi) ; -> (hello (there (general kenobi)))
