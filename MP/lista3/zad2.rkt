#lang racket

(define lista `(1 2 3 4))

(define (my-foldl f x xs)
  (define (it xs acc)
    (if (null? xs)
        acc
        (it (cdr xs) (f (car xs) acc))))
  (it xs x))

(define (product l) (my-foldl * 1 l))

(product lista)
