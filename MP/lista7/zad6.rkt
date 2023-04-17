#lang racket

(define/contract (my-foldr f x xs)
  ( parametric->/c [ a b ] (-> (-> a b b ) b ( listof a ) b ) )
  (if (null? xs)
      x
      (f (car xs) (my-foldr f x (cdr xs)))))