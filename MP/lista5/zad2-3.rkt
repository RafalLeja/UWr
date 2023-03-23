#lang plait

;(('a -> 'b) 'a -> 'b)
(define (apply f x) (f x))

;(('a -> 'b) ('c -> 'a) -> ('c -> 'b))
(define (compose f g) (lambda (x) (f (g x))))

;(('a 'b -> 'c) -> ('b 'a -> 'c))
(define (flip f) (lambda (x y) (f y x)))

;(('a 'b -> 'c) -> ('a -> ('b -> 'c)))
(define (curry f) (lambda (x) (lambda (y) (f x y))))

;(('_a -> '_b) -> (('_c -> '_a) -> ('_c -> '_b)))
(curry compose)

;(('_a -> ('_b -> '_c)) -> ('_a -> (('_d -> '_b) -> ('_d -> '_c))))
((curry compose) (curry compose))

;(('_a -> ('_b -> '_c)) -> ('_a -> ('_b -> '_c)))
((curry compose) (curry apply))

;(('_a -> '_b) -> (('_c -> '_a) -> ('_c -> '_b)))
((curry apply) (curry compose))

;(('_a '_b -> '_c) -> ('_b -> ('_a -> '_c)))
(compose curry flip)