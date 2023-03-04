#lang racket

(define (fib n)
   (if (< n 2) 
   n 
   (+ 
      (fib (- n 1)) 
      (fib (- n 2)))))

(define (fib-iter n) ; duuuużo szybsza
   (define (it a b dest)
      (if (= dest 0)
         a
         (it b (+ a b) (- dest 1))))
   (it 0 1 n))

; fib powtarza obliczenia dla każdego (fib n-2)

; fib-iter oblicza po kolei wszystkie elementy ciągu