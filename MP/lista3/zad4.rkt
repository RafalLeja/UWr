#lang racket

(define (sqare a) 
   (* a a))

(define (inc a)
   (+ a 1))

(define (my-compose f g) 
   (lambda (x) (f (g x))))

((my-compose sqare inc) 5)
((my-compose inc sqare) 5)