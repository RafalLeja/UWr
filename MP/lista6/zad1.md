```rust
(define (map f xs)
  (if (empty? xs)
    xs
    (cons (f (first xs)) (map f (rest xs)))))
```
# Lemat
P := (map g xs) &equiv; vs

* P(empty)
 
  L &equiv; (map g empty) &equiv; empty 
  
  zatem: P &equiv; vs &equiv; empty  

* Weźmy dowolną funkcje g i listę xs. Załóżmy, że istnieje vs t. że. (map g xs) &equiv; vs. Pokażemy, że istnieje vs' t. że. (map g (cons x xs)) &equiv; vs'.

  L &equiv; (map g (cons x xs)) &equiv; (cons (g x) (map g xs)) &equiv; (cons (g x) vs) \
  Stąd istnieje vs' &equiv; (cons (g x) vs) , które jest listą, bo z założenia vs jest listą.
# dowód indukcyjny

Weźmy dowolne `f, g, xs`. Niech `P(xs) := (map f (map g xs)) ≡ (map (lambda (x) (f (g x))) xs)`

* `P(empty)`
  
  `L ≡ (map f (map g empty)) ≡ (map f empty) ≡ empty`
  
  `P ≡ (map (lambda(X) (f (g x))) empty) ≡ empty ≡ L`

* Weźmy dowolne `f, g, xs`. Załóżmy, że `(map f (map g xs)) ≡ (map (lambda (x) (f (g x))) xs)`. Pokażemy że `(map f (map g (cons x xs))) ≡ (map (lambda (x) (f (g x))) (cons x xs))`.


  `L ≡ (map f (map g (cons x xs)))` $≡^{def. \ map}$ `(map f (cons (g x) (map g xs))) ≡ (map f (cons (g x) vs)) ≡ (cons (f (g x)) (map f vs)) ≡ (cons (f (g x)) (map (lambda (x) (f (g x)) xs))) ≡ (cons (f (g x)) (map (lambda (x) (f (g x) xs)))) ≡ L`
  
