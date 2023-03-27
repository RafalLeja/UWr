#lang plait

;('a 'b -> 'a)
(define (f1 a b)
  a)
;(('a 'b -> 'c) ('a -> 'b) 'a -> 'c)
(define (f2 f g x)
  (f x (g x)))
;((('a -> 'a) -> 'a) -> 'a)
(define (i x) x)
(define (pom h ii) (ii (h ii)))
(define (f3 h) (pom h i))
;(define (f3 h) (i (h i)))
;(('a -> 'b) ('a -> 'c) -> ('a -> ('b *'c)))
(define (f4 f g)
  (lambda (x) (values (f x) (g x))))
;(('a -> (Optionof ('a * 'b))) 'a -> (Listof 'b))
(define (f5 f x)
  (type-case (Optionof 'x) (f x)
    ((none) '())
    ((some n)
     (if (some? (f (fst n)))
         (list (snd n))
         '()))))
  





  


