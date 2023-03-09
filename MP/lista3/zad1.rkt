#lang racket

;1
'(( car ( a . b ) ) (* 2) )

(list `(car (a . b)) `(* 2))

;2
`( ,( car '( a . b ) ) ,(* 2) )

(list (car '(a . b)) (* 2))

;3
'((+ 1 2 3) (cons) (cons a b) )

(list '(+ 1 2 3) '(cons) '(cons a b))