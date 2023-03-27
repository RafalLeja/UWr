#lang plait

(define (apply f x) (f x))
;(('a -> 'b) 'a -> 'b)
;bierze jako argumenty funkcje ('a -> 'b) i a, zwraca funkcje od a, czyli b
(define (compose f g) (lambda (x) (f (g x))))
;(('a -> 'b) ('c -> 'a) -> ('c -> 'b))
;bierze jako argumenty funkcje f: a->b i g: c->a
;g dziala na czyms i zwraca a, aplikuje do f wiec zwraca b
(define (flip f) (lambda (x y) (f y x)))
;(('a 'b -> 'c) -> ('b 'a -> 'c))
;bierze jako argument funkcje f: (a b -> c) i zwraca f z odwrocona kolejnoscia argumentow
(define (curry f) (lambda (x) (lambda (y) (f x y))))
;(('a 'b -> 'c) -> ('a -> ('b -> 'c)))
;bierze funkcje ktora przyjmuje 2 argumenty i zwraca nowa funkcje, ktora przyjmuje argument x i zwraca funkcje przyjmujaca y
