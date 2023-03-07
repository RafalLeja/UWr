#lang racket

(define lista (list 6 3 4 5 0 7 1 2))

(define (elem? x l) 
   (if (= x (car l))
      #t 
      (if (null? (cdr l))
         #f
         (elem? x (cdr l)))))

(define (maximum l)
   (define (itr x l)
      (if (null?  l)
         x
         (if (> x (car l))
            (itr x (cdr l))
            (itr (car l) (cdr l)))))
   (itr -inf.0 l))

(define (minimum l)
   (define (itr x l)
      (if (null?  l)
         x
         (if (< x (car l))
            (itr x (cdr l))
            (itr (car l) (cdr l)))))
   (itr +inf.0 l))

(define (suffixes l)
   (if (null? l)
      (cons l null)  
      (cons l (suffixes (cdr l)))))

(define (sorted? l)
   (define (itr p l)
      (if (null? l)
      #t
      (if (> p (car l))
         #f
         (itr (car l) (cdr l)))))
   (itr -inf.0 l))

(define (rmv e l)
   (if (null? l)
      l
      (if (= e (car l))
      (cdr l)
      (cons (car l) (rmv e (cdr l))))))

(define (select l)
   (define min (minimum l))
   (cons min (rmv min l)))

(define (selection-sort l)
   (if (null? l)
      l
      (cons (car (select l)) (selection-sort (cdr (select l))))))

