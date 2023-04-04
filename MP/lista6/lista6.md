# Lista 6

### Zadanie 1

#### Teza

(map (lambda (x) (f (g x))) xs) $\equiv$ (map f (map g xs))

#### Dowód (indukcja)

 1. - L = (map (lambda (x) (f (g x))) empty) $\equiv$ empty
    - P = (map f (map g empty)) $\equiv$ (map f empty) $\equiv$ empty = L
2. Załóżmy, że (map (lambda (x) (f (g x))) xs) $\equiv$ (map f (map g xs)). Pokażemy, że (map (lambda (x) (f (g x))) (cons x xs)) $\equiv$ (map f (map g (cons x xs))).
   - L = (map (lambda (x) (f (g x))) (cons x xs)) $\equiv$ (cons (f (g x)) (map (lambda (x) (f (g x))) xs))
   - P = (map f (map g (cons x xs))) $\equiv$ (map f (cons (g x) (map g xs))) $\equiv$ (cons (f (g x)) (map f (map g xs))) = L *(Ponieważ z zał. wiemy, że (map (lambda (x) (f (g x))) xs) $\equiv$ (map f (map g xs)))*

### Zadanie 2

#### Teza

$\exists$zs (append xs ys) $\equiv$ zs

#### Dowód (indukcja względem xs)

1. (append empty ys) $\equiv$ ys
2. Załóżmy, że istnieje zs $\equiv$ (append xs ys). Pokażemy, że istnieje zs' $\equiv$ (append (cons x xs) ys).
   - (append (cons x xs) ys) $\equiv$ (cons x (append xs ys)) $\equiv$ (cons x zs), a z założenia wiemy, że zs istnieje

### Zadanie 3

```racket
(define-type (NNF 'v)
    (nnf-lit [polarity : Boolean] [var : 'v])
    (nnf-conj [l : (NNF 'v)] [r : (NNF 'v)])
    (nnf-disj [l : (NNF 'v)] [r : (NNF 'v)]))
```

#### Zasada Indukcji

Niech **P** będzie własnością t.ż.
1. **P**(nnf-lit polarity v)
2. Dla dowolnych wartości l, r, jeżeli zachodzi **P**(l) i **P**(r), to **P**(nnf-conj l r)
3. Dla dowolnych wartości l, r, jeżeli zachodzi **P**(l) i **P**(r), to **P**(nnf-disj l r)

Wówczas zachodzi **P**($\varphi$) dla dowolengo $\varphi$.

### Zadanie 4

```rust
(define (neg-nnf v)
   (cond [(nnf-lit? v) (nnf-list (not (nnf-lit-polarity v) nnf-lit-var))]
         [(nnf-conj? v) (nnf-disj (neg-nnf l) (neg-nnf r))]
         [(nnf-disj? v) (nnf-conj (neg-nnf l) (neg-nnf r))]))
```

#### Teza

(neg-nnf (neg-nnf $\varphi$)) $\equiv$ $\varphi$

#### Dowód (przez indukcję)

1. L = (neg-nnf (neg-nnf (nnf-lit polarity v))) $\equiv$ (neg-nnf (nnf-lit (not polarity) v)) $\equiv$ (nnf-lit polarity v) = P
2. Załóżmy, że zachodzi (neg-nnf (neg-nnf l)) $\equiv$ l oraz (neg-nnf (neg-nnf r)) $\equiv$ r. Pokażemy, że zachodzi (neg-nnf (neg-nnf (nnf-conj l r))) $\equiv$ (nnf-conj l r).
   - L = (neg-nnf (neg-nnf (nnf-conj l r))) $\equiv$ (neg-nnf (nnf-disj (neg-nnf l) (neg-nnf r))) $\equiv$ (nnf-conj (nnf-neg (nnf-neg l)) (nnf-neg (nnf-neg r))) $\equiv$ (nnf-conj l r) = P
3. Załóżmy, że zachodzi (neg-nnf (neg-nnf l)) $\equiv$ l oraz (neg-nnf (neg-nnf r)) $\equiv$ r. Pokażemy, że zachodzi (neg-nnf (neg-nnf (nnf-disj l r))) $\equiv$ (nnf-disj l r).
   - L = (neg-nnf (neg-nnf (nnf-disj l r))) $\equiv$ (neg-nnf (nnf-conj (neg-nnf l) (neg-nnf r))) $\equiv$ (nnf-disj (nnf-neg (nnf-neg l)) (nnf-neg (nnf-neg r))) $\equiv$ (nnf-disj l r) = P

### Zadanie 5

```rust
(define (eval-nnf sig nnf)
  (cond 
    [(nnf-lit? nnf) (if (nnf-lit-polarity nnf)
                      (sig (nnf-lit-var nnf))
                      (not (sig (nnf-lit-var nnf))))]
    [(nnf-conj? nnf) (and (eval-nnf sig (nnf-conj-l nnf)) (eval-nnf sig (nnf-conj-r nnf)))]
    [(nnf-disj? nnf) (or (eval-nnf sig (nnf-disj-l nnf)) (eval-nnf sig (nnf-disj-r nnf)))]))
```
#### Teza

(eval-nnf $\sigma$ (neg-nnf $\varphi$)) $\equiv$ (not (eval-nnf $\sigma$ $\varphi$))

#### Dowód (przez indukcję)

1. L = (eval-nnf $\sigma$ (neg-nnf (nnf-lit polarity v))) $\equiv$ (eval-nnf $\sigma$ (nnf-lit (not polarity) v)) $\equiv$ (not (eval-nnf $\sigma$ (nnf-lit polarity v))) = P
2. Załóżmy, że zachodzi (eval-nnf $\sigma$ (neg-nnf l)) $\equiv$ (not (eval-nnf $\sigma$ l)) oraz (eval-nnf $\sigma$ (neg-nnf r)) $\equiv$ (not (eval-nnf $\sigma$ r)). Pokażemy, że zachodzi (eval-nnf $\sigma$ (neg-nnf (nnf-conj l r))) $\equiv$ (not (eval-nnf $\sigma$ (nnf-conj l r)))
   - L = (eval-nnf $\sigma$ (neg-nnf (nnf-conj l r))) $\equiv$ (eval-nnf $\sigma$ (nnf-disj (neg-nnf l) (neg-nnf r))) $\equiv$ (or (eval-nnf $\sigma$ (neg-nnf l)) (eval-nnf $\sigma$ (neg-nnf r))) $\equiv$ (or (not (eval-nnf $\sigma$ l) (not (eval-nnf $\sigma$ r)))) $\equiv$ (not (and (eval-nnf $\sigma$ l) (eval-nnf $\sigma$ r))) $\equiv$ (not (eval-nnf $\sigma$ (nnf-conj l r))) = P
3. Załóżmy, że zachodzi (eval-nnf $\sigma$ (neg-nnf l)) $\equiv$ (not (eval-nnf $\sigma$ l)) oraz (eval-nnf $\sigma$ (neg-nnf r)) $\equiv$ (not (eval-nnf $\sigma$ r)). Pokażemy, że zachodzi (eval-nnf $\sigma$ (neg-nnf (nnf-disj l r))) $\equiv$ (not (eval-nnf $\sigma$ (nnf-disj l r)))
   - L = (eval-nnf $\sigma$ (neg-nnf (nnf-disj l r))) $\equiv$ (eval-nnf $\sigma$ (nnf-conj (neg-nnf l) (neg-nnf r))) $\equiv$ (and (eval-nnf $\sigma$ (neg-nnf l)) (eval-nnf $\sigma$ (neg-nnf r))) $\equiv$ (and (not (eval-nnf $\sigma$ l) (not (eval-nnf $\sigma$ r)))) $\equiv$ (not (or (eval-nnf $\sigma$ l) (eval-nnf $\sigma$ r))) $\equiv$ (not (eval-nnf $\sigma$ (nnf-disj l r))) = P