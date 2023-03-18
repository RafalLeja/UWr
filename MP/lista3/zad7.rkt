#lang racket

(define lista `(1 2 3 4 5))

(define (my-foldr f x xs)
  (if (null? xs)
      x
      (f (car xs) (my-foldr f x (cdr xs)))))

(define (foldr-reverse xs)
   (foldr 
      (lambda (y ys) 
         (append ys (list y))) 
      null xs))





; foldr-reverse uzywa appenda -> czyli doklejania nowej listy na koniec starej
; kiedy dodajemy wiec nowy elemnt musimy przejsc wszystkie pozostale wczesniej
; najpierw mamy 10000 - > 10000 9999 -> 10000 9999 9998 -> ...
; dojdzie wiec do przepelnienia pamieci
; nieuzytkami beda wiec wszystkie podlisty ktore nie daja jeszcze koncowego wyniku
; otrzymamy ciag ayrtmetyczny wiec consow bedzie n * (n+1) / 2