#lang racket

(define empty-set
    #f)

(define (singleton a)
    (lambda (x) (equal? a x)))

(define (in a s)
    (s a))

(define (union s t)
    (lambda (x) (or (s x) (t x))))

(define (intersect s t)
    (lambda (x) (and (s x) (t x))))