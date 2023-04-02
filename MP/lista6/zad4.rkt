#lang plait

(define-type (NNF 'v)
(nnf-lit [polarity : Boolean] [var : 'v])
(nnf-conj [l : (NNF 'v)] [r : (NNF 'v)])
(nnf-disj [l : (NNF 'v)] [r : (NNF 'v)]))

(define (neg-nnf v)
  (cond 
    [(nnf-lit? v) (nnf-lit (not (nnf-lit-polarity v)) nnf-lit-var)]
    [(nnf-conj? v) (nnf-conj (neg-nnf (nnf-conj-l v)) (neg-nnf (nnf-conj-r v)))]
    [(nnf-disj? v) (nnf-disj (neg-nnf (nnf-disj-l v)) (neg-nnf (nnf-disj-r v)))]))