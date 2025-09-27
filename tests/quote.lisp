(a b) ; -> (a b)
(a b c) ; -> (a (b c))
((a b) c) ; -> ((a b) c)
(a (b c)) ; -> (a (b c))
(a b c d) ; -> ((a b)(c d))

('a b) ; -> ((quote a) b)
(a 'b) ; -> (a (quote b))
('a 'b) ; -> ((quote a) (quote b))

(a '(b c)) ; -> (a (quote (b c)))
('(a b) c) ; -> ((quote (a b)) c)

('a '(b c)) ; -> ((quote a) (quote (b c)))
('(a b) 'c) ; -> ((quote (a b)) (quote c))
