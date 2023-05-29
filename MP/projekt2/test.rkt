#lang racket
(require data/heap)
(require racket/trace)

(define a (make-heap <=))

(heap-add! a (cons 1 2))