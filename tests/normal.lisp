; This file is for test the lexer_normalizeList()
; function for adding in extra parentheses to make the cons cells explicit 

(a b) ; -> (a b)
(a b c) ; -> (a (b c))
((a b) c) ; -> ((a b) c)
(a (b c)) ; -> (a (b c))

(a b c d) ; -> (a (b (c d)))
(a b c d e) ; -> (a (b (c (d e))))

((a b) c d) ; -> ((a b) (c d))
(a (b c) d) ; -> (a ((b c) d))
(a b (c d)) ; -> (a (b (c d)))
