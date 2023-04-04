# Zadanie 2
```rust
(define (append xd ys)
  (if (empty? xs)
    ys
    (cons (first xs) ( append (rest xs) ys))))
```

## Teza: $\exists$ zs => (append xs ys) &equiv; zs

* P(empty)
   
  L &equiv; (append empty ys) &equiv; ys &equiv; zs 

* Załóżmy że istnieje zs &equiv; (append xs ys). Pokażemy że istnieje zs' &equiv; (append (cons x xs) ys).

  (append (cons x xs) ys) &equiv; (cons x (append xs ys)) &equiv; (cons x zs), a z załozenia wiemy, że zs istnieje