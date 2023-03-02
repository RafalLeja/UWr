#lang racket/base

(define (f x y z) 
    (- (+ (expt x 2) (expt y 2) (expt z 2)) (expt (min x y z) 2)))


(provide f)