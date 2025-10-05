
(set rectLength 4)
(set rectWidth 6)
(define area (height width) (* height width))
(set rectArea (area rectLength rectWidth))
(rectArea)

(set x 4)
(set y 5)
(set z 6)

(define square (x) (* x x))
(square x)
(square y)
(square z)

(square (square 2))
(* 2 (square 3))

(define volume (height length width) (* height (* width length)))
(volume 2 3 4)
