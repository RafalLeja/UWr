#lang plait

(define (remove x lst)
  (cond
    ((empty? lst) '())  ; jeśli lista jest pusta, zwracamy pustą listę
    ((eq? x (first lst)) (remove x (rest lst))) ; jeśli pierwszy element listy to x, to pomijamy go i rekurencyjnie usuwamy z reszty listy
    (else (cons (first lst) (remove x (rest lst)))))) ; w przeciwnym przypadku zachowujemy pierwszy element i rekurencyjnie usuwamy z reszty listy

(define (append-map f lst)
  (foldr (lambda (x acc)
           (append (f x) acc))
         '()
         lst))

(define (perms lst)
  (if (empty? lst)
      '(())
      (append-map (lambda (x)
                    (map (lambda (p) (cons x p))
                         (perms (remove x lst))))
                  lst)))

(perms (list 1 2 3))