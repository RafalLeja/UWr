#lang racket

(define lista `(1 2 3 4 5))

(define (my-foldr f x xs)
  (if (null? xs)
      x
      (f (car xs) (my-foldr f x (cdr xs)))))

(define (foldr-reverse xs)
   (foldr 
      (lambda (y ys) 
         (append ys (list y))) 
      null xs))