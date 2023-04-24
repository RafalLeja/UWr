#lang racket

(define x 
  (mcons 1 (mcons 2 (mcons 3 null))))

;zad1

(define (cycle! q)
  (define (itr beginning i)
    (if (null? (mcdr i))
      (set-mcdr! i beginning)
      (itr beginning (mcdr i))))
  (itr q q))

;zad2

(define (mreverse! q)
  (define (itr p c)
    (if (null? (mcdr c)) 
      (set-mcdr! c p)
      (begin 
        (itr c (mcdr c))
        (set-mcdr! c p))))
  (itr q (mcdr q)))