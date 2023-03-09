#lang racket

(define (build-list n f)
   (define (itr idx func dest)
      (if (= idx dest)
         `()
         (cons (func idx dest) (itr (+ idx 1) func dest))))
   (itr 0 f n))

(define odejmij 
   (lambda (x y) (- 0 (+ x 1))))

(define odwroc
   (lambda (x y) (/ 1 (+ x 1))))

(define oparz 
   (lambda (x y) (* 2 x)))

(define (pomoc-macierz mark idx dest)
      (cond 
         [(= idx dest) `()]
         [(= idx mark) (cons 1 (pomoc-macierz mark (+ idx 1) dest))]
         [else (cons 0 (pomoc-macierz mark (+ idx 1) dest))]))

(define macierzuj
   (lambda (x y ) (pomoc-macierz x 0 y)))

(define (negatives n) 
   (build-list n odejmij))

(define (reciprocals n)
   (build-list n odwroc))

(define (evens n)
   (build-list n oparz))

(define (identityM n)
   (build-list n macierzuj))

(negatives 5)

(reciprocals 5)

(evens 5)

(identityM 5)