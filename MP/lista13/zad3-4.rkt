#lang racket

(define-syntax-rule
  (stream-cons v s)
  (cons v (delay s)))

(define stream-car car)

(define (stream-cdr s)
  (force (cdr s)))

(define stream-null null)
(define stream-null? null?)

(define (map2 f xs ys)
  (stream-cons
   (f (stream-car xs)
      (stream-car ys))
   (map2 f (stream-cdr xs) (stream-cdr ys))))

(define (integers-from n)
  (stream-cons n (integers-from (+ n 1))))

(define (test-stream s i)
  (if (= 0 i)
    (void)
    (begin 
      (displayln (stream-car s))
      (test-stream (stream-cdr s) (- i 1)))))

(define S
  (stream-cons 1 (map2 * (integers-from 2) S)))

(define (partial-sums s)
  (stream-cons 
    (stream-car s) 
    (map2 + (partial-sums s) (stream-cdr s))))
