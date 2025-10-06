
(set rectLength 4) ; -> 4
(set rectWidth 6) ; -> 6
(define area (height width) (* height width))
(set rectArea (area rectLength rectWidth)) ; -> 24
(rectArea) ; -> 24

(set x 4) ; -> 4
(set y 5) ; -> 5
(set z 6) ; -> 6

(define square (x) (* x x))
(square x) ; -> 16
(square y) ; -> 25
(square z) ; -> 36

(square (square 2)) ; -> 16
(* 2 (square 3)) ; -> 18

(define volume (height length width) (* height (* width length)))
(volume 2 3 4) ; -> 24

((lambda (x) (x)) 3) ; -> 3
((lambda (x y) (+ x y)) 2 4) ; -> 6
((lambda (x y z) (* x (* y z))) 2 3 4) ; -> 24

(define cube (x) ((lambda (a) (* a ( * a a))) x)) ; -> true
(cube 3) ; -> 27
