#lang racket

;1
'(( car ( a . b ) ) (* 2) )

(list (list `car (cons `a `b)) (list `* 2))

;(list `(car (a . b)) `(* 2))

;2
`( ,( car '( a . b ) ) ,(* 2) )

(list (car (cons `a `b)) (* 2))

;(list (car '(a . b)) (* 2))

;3
'((+ 1 2 3) (cons) (cons a b) )

(list (list `+ 1 2 3) (list `cons) (list `cons `a `b))

;(list '(+ 1 2 3) '(cons) '(cons a b))