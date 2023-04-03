```rust
(define-type (NNF 'v)
(nnf-lit [polarity : Boolean] [var : 'v])
(nnf-conj [l : (NNF 'v)] [r : (NNF 'v)])
(nnf-disj [l : (NNF 'v)] [r : (NNF 'v)]))
```