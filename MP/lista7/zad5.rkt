#lang racket

(define (foldl-map f a xs)
  (parametric->/c [x y z] (-> (-> x y (cons/c z y)) y (listof x) (cons/c (listof z) y)))
  (define (it a xs ys)
    (if (null? xs)
      (cons (reverse ys) a)
      (let [(p (f (car xs) a)) ]
        (it (cdr p)
          (cdr xs)
          (cons (car p) ys)))))
  (it a xs null))
