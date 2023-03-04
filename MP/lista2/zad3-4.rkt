#lang racket

(define-struct matrix (a b c d) #:transparent)

(define (matrix-mult x y) 
   (make-matrix 
      (+ (* (matrix-a x) (matrix-a y)) (* (matrix-b x) (matrix-c y)))
      (+ (* (matrix-a x) (matrix-b y)) (* (matrix-b x) (matrix-d y)))
      (+ (* (matrix-c x) (matrix-a y)) (* (matrix-d x) (matrix-c y)))
      (+ (* (matrix-d x) (matrix-d y)) (* (matrix-c x) (matrix-b y)))
      ))

(define matrix-id (make-matrix 1 0 0 1))

(define (matrix-add x y) 
   (make-matrix 
      (+ (matrix-a x) (matrix-a y))
      (+ (matrix-b x) (matrix-b y))
      (+ (matrix-c x) (matrix-c y))
      (+ (matrix-d x) (matrix-d y))
      ))

(define (matrix-expt m k)
   (define (it base acc dest)
      (if (= dest 0)
         acc
         (it base (matrix-mult base acc) (- dest 1))))
   (it m (make-matrix 1 1 1 1) k))

(define (fib-matrix k)
   (matrix-expt (make-matrix 1 1 1 0) k))

(define (matrix-expt-fast m k)
   (define (it base acc dest)
      (if (= dest 0)
         acc
         (if (= 0 (modulo dest 2))
            (it (matrix-mult base base) acc (/ dest 2))
            (it base (matrix-mult base acc) (- dest 1)))))
   (it m (make-matrix 1 1 1 1) k))

(define (fib-matrix-fast k)
   (matrix-expt-fast (make-matrix 1 1 1 0) k))