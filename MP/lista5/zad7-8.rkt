#lang plait

(define-type Prop
    (var [v : String])
    (conj [l : Prop] [r : Prop])
    (disj [l : Prop] [r : Prop])
    (neg [f : Prop]))

(define test
    (conj (disj (var "a") (var "b")) (neg (var "c"))))

(define (free-vars-iter p [l : (Listof String)])
    (cond 
        [(conj? p) (free-vars-iter (conj-r p) (free-vars-iter (conj-l p) l))]
        [(disj? p) (free-vars-iter (disj-r p) (free-vars-iter (disj-l p) l))]
        [(neg? p)  (free-vars-iter (neg-f p) l)]
        [else 
            (if (member (var-v p) l)
                l
                (append (list (var-v p)) l))]))

(define (free-vars [prop : Prop])
    (free-vars-iter prop empty ))

;zadanie 8

(define (eval [hash : (Hashof String Boolean)] prop)
    (cond 
        [(conj? prop) (and (eval hash (conj-l prop)) (eval hash (conj-r prop)))]
        [(disj? prop) (or (eval hash (disj-l prop)) (eval hash (disj-r prop)))]
        [(neg? prop) (not (eval hash (neg-f prop)))]
        [else 
            (if (none? (hash-ref hash (var-v prop)))
                #f
                (some-v (hash-ref hash (var-v prop))))]))

(define test-hash
    (hash (list (pair "a" #t) (pair "b" #f) (pair "c" #t))))

