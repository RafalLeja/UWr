#lang racket

(define pl 
  (list 
  (lambda () (+ 1 2 1))
  (lambda () (+ 1 2 2))
  (lambda () (print "aba"))
  (lambda () (print "aa"))))
