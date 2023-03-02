#lang racket
(define (jezeli x y z)
    (or (and x y) (or x z)))