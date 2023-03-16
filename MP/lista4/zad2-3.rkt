#lang racket

(define-struct leaf () #:transparent)
(define-struct node (l elem r) #:transparent)

(define example-tree
  (node (node (leaf) 1 (leaf))
        2
        (node (node (leaf) 3 (leaf))
              4
              (leaf))))

(define bst-tree
    (node (node (leaf) 1 (leaf))
          2
          (node (leaf) 3 (leaf))))

(define (my-foldr f x xs)
  (if (null? xs)
      x
      (f (car xs) (my-foldr f x (cdr xs)))))

(define (fold-tree f x t)
  (if (leaf? t)
      x
      (f (node-elem t) (fold-tree f x (node-l t)) (fold-tree f x (node-r t)))))

(define (tree-sum t)
    (fold-tree + 0 t))

(define (tree-flip t)
    (fold-tree (lambda (x y z) (make-node z x y)) (leaf) t))

(define (tree-height t)
    (fold-tree (lambda (x y z) (+ (max y z) 1)) 0 t))

(define (tree-span t)
    (fold-tree (lambda (x y z) (cons 
                                    (min x (car y))
                                    (max x (cdr z))))
                                (cons +inf.0 -inf.0) t))

(define (flatten t)
    (fold-tree (lambda (x y z) (list x y z)) null t))

(define (bst? t)
    (define (itr prev t dir)
    (cond 
        [(leaf? t) #t]
        [(and (= dir -1) (>= (node-elem t) prev)) #f]
        [(and (= dir 1) (< (node-elem t) prev)) #f]
        [else (and (itr (node-elem t) (node-l t) -1)
                    (itr (node-elem t) (node-r t) 1))]))
    (and (itr (node-elem t) (node-l t) -1)
        (itr (node-elem t) (node-r t) 1)))

(define (sum-paths t)
    (define (itr sum t)
        (if (leaf? t)
            (leaf)
            (node 
                (itr (+ sum (node-elem t)) (node-l t))
                (+ sum (node-elem t))
                (itr (+ sum (node-elem t)) (node-r t)))))
    (itr 0 t))
