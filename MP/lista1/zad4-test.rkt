#lang racket/base

(require rackunit "zad4.rkt")

(check-equal? (f 1 2 3) 13 "test (f 1 2 3) = 3")

(check-equal? (f 4 5 6) 61 "test (f 4 5 6) = 61")

(check-equal? (f 0 0 0) 0 "test (f 0 0 0) = 0")
