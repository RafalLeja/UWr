#lang racket

(define (suffixes l)
  (if (null? l)
    (cons l null)  
    (cons l (suffixes (cdr l)))))

(define/contract (csuffixes l)
  (parametric->/c [a] (-> (listof a) (listof (listof a))))
  (if (null? l)
      (cons l null)  
      (cons l (suffixes (cdr l)))))

(time (suffixes (range 3000)) (void))
(time (csuffixes (range 3000)) (void))