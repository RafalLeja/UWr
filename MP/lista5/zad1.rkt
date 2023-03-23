#lang plait

(define (1fun a b) 
    a)

(define (2fun a b c)
    (a c (b c)))

(define (3fun a)
    (a (a 'a)))
