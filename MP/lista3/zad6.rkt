#lang racket

(define empty-set
    #f)

(define (singleton a)
    (lambda (b) (equal? b a)))

(define (in a s)
    (= #t (s a)))

(define (union a b)
    (lambda (x) (or (a x) (b x))))

(define (intersect a b)
    (lambda (x) (and (a x) (b x))))