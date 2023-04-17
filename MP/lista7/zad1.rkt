#lang plait

(define-type (2-Tree 'a)
  (leaf)
  (2-node [l : (2-Tree 'a)] [elem : 'a] [r : (2-Tree 'a)])
  (3-node [l : (2-Tree 'a)] [a : 'a] [m : (2-Tree 'a)] [b : 'a] [r : (2-Tree 'a)]))


(define (2-Tree? t)
  (define (itr a)
    (cond 
      [(leaf? a) ]
      [(2-Tree? a) (and )]))
  (cond 
    [(leaf? t) #t]
    [(2-node? t) ]))
