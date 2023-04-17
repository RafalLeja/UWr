#lang racket

(define (foldl-map f a xs)
  (parametric->/c [x y] (-> (-> x y (values x y)) y (listof x) (values (listof y) y)))
  (define (it a xs ys)
    (if (null? xs)
      (cons (reverse ys) a)
      (let [(p (f (car xs) a)) ]
        (it (cdr p)
          (cdr xs)
          (cons (car p) ys)))))
  (it a xs null))
