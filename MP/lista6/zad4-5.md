```rust

(define-type (NNF 'v)
(nnf-lit [polarity : Boolean] [var : 'v])
(nnf-conj [l : (NNF 'v)] [r : (NNF 'v)])
(nnf-disj [l : (NNF 'v)] [r : (NNF 'v)]))

(define (neg-nnf v)
  (cond 
    [(nnf-lit? v) (nnf-lit (not (nnf-lit-polarity v)) nnf-lit-var)]
    [(nnf-conj? v) (nnf-disj (neg-nnf (nnf-conj-l v)) (neg-nnf (nnf-conj-r v)))]
    [(nnf-disj? v) (nnf-conj (neg-nnf (nnf-disj-l v)) (neg-nnf (nnf-disj-r v)))]))

(define (eval-nnf sig nnf)
  (cond 
    [(nnf-lit? nnf) (if (nnf-lit-polarity nnf)
                      (sig (nnf-lit-var nnf))
                      (not (sig (nnf-lit-var nnf))))]
    [(nnf-conj? nnf) (and (eval-nnf sig (nnf-conj-l nnf)) (eval-nnf sig (nnf-conj-r nnf)))]
    [(nnf-disj? nnf) (or (eval-nnf sig (nnf-disj-l nnf)) (eval-nnf sig (nnf-disj-r nnf)))]))
```

# Zadanie 4

