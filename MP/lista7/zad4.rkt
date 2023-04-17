#lang racket

;                                \/
;(parametric->/c [ a b ] (a b -> a))

(define/contract (func1 x y)
  (parametric->/c [ a b ] (-> a b a) )
  y)

;                               \/\/       \/           \/
;( parametric- >/ c [ a b c ] ((a b -> c) (a -> b) a -> c))

(define/contract (func2 x y z)
  ( parametric->/c [ a b c ] (-> (-> a b c ) (-> a b ) a c ))
  z)

;( parametric- >/ c [ a b c ] (- > (- > b c ) (- > a b ) (- > a c ) ) )
;( parametric- >/ c [ a ] (- > (- > (- > a a ) a ) a ) )
