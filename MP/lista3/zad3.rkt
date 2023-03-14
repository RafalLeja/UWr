#lang racket

; (+ 1 (* 1 2)) == 3
(( lambda ( x y ) (+ x (* x y ) ) ) 1 2)

;#<procedure> | (x => x)(x => x) = (x => x) = x
(( lambda ( x ) x ) ( lambda ( x ) x ) )

;#<procedure> | (x => (x x))(x => x) = ((x => x) (x => x)) = (x => x) = x
(( lambda ( x ) ( x x ) ) ( lambda ( x ) x ) )

;inf | (x => X(x))(x => X(x)) => ...
(( lambda ( x ) ( x x ) ) ( lambda ( x ) ( x x ) ) )