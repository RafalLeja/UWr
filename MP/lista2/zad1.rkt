#lang racket

; x - wolna

#;(let ([x 3])
    (+ x y))    ; x zwiazana, y wolna

#;(let ([x 1]
   [y (+ x 2)])
    (+ x y)) ; x zwiazany z [x 1], ale nie z [y (+ x 2)]
             ; y zwiazany z [y (+ x 2)]

#;(let ([x 1]
   (let [y (+ x 2)])
      (* x y))) ; x zwiazany z [x 1] i z [y (+ x 2)]
                ; y zwiazany z [y (+ x 2)]

(define (f x y)
   (* x y z))  ; x, y zwiazany z (f x y), z wolna

(define (ff x)
   (define (g y z)
      (* x y z))
      (f x x x)) ; x zwiazany (ff x); y, z zwiazany z (g y z)

