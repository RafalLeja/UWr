#lang racket

(define-struct matrix (a b c d) #:transparent)

(define (matrix-mult x y) 
   (make-matrix 
      (* (matrix-a x) (matrix-a y))
      (* (matrix-b x) (matrix-b y))
      (* (matrix-c x) (matrix-c y))
      (* (matrix-d x) (matrix-d y))
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
      (if (= dest 1)
         acc
         (it base (matrix-mult base acc) (- dest 1))))
   (it m m k))

(define (fib-matrix k)
   (define (it a b dest)
      (if (= dest 0)
         a
         (it b (matrix-add a b) (- dest 1))))
   (it (make-matrix 1 1 1 0) (make-matrix 2 1 1 1) k))

(define (matrix-expt-fast m k)
   (define (it base acc dest)
      (if (= dest 0)
         acc
         (if (= 0 (modulo dest 2))
            (it (matrix-mult base base) acc (/ k 2))
            (it base (matrix-mult base acc) (- k 1)))))
   (it m (make-matrix 1 1 1 1) k))