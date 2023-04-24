#lang plait

(define (expt a b)
  (if (= b 0)
    1
    (* a (expt a (sub1 b)))))

(define (fact n)
  (if (= n 0) 1
      (* n (fact (- n 1)))))

(define (inv n)
  (- 0 n))

(define-type Op
  (op-add) (op-mul) (op-sub) (op-div) (op-pow))

(define-type Uop
  (op-fact) (op-inv))

(define-type Exp
  (exp-number [n : Number])
  (exp-op [op : Op] [e1 : Exp] [e2 : Exp])
  (exp-uop [op : Uop] [e1 : Exp]))

(define (parse-Op s)
  (let ([sym (s-exp->symbol s)])
  (cond
    [(equal? sym '+) (op-add)]
    [(equal? sym '-) (op-sub)]
    [(equal? sym '*) (op-mul)]
    [(equal? sym '/) (op-div)]
    [(equal? sym '^) (op-pow)])))

(define (parse-Uop s)
  (let ([sym (s-exp->symbol s)])
  (cond
    [(equal? sym '!) (op-fact)]
    [(equal? sym '-) (op-inv)])))

(define (parse-Exp s)
  (cond
    [(s-exp-number? s) (exp-number (s-exp->number s))]
    [(s-exp-list? s)
     (let ([xs (s-exp->list s)])
        (if (equal? 2 (length xs))
          (exp-uop 
            (parse-Uop (first xs)) 
            (parse-Exp (second xs)))
          (exp-op 
            (parse-Op  (first  xs))
            (parse-Exp (second xs))
            (parse-Exp (third  xs)))))]))

(define (my-parse s)
  (cond
    [(s-exp-number? s) (s-exp->number s)]
    [(s-exp-list? s)
      (let 
        ([xs (s-exp->list s)]
        [op (s-exp->symbol (first (s-exp->list s)))])
        (if (= 2 (length xs))
          (cond
            [(equal? '- op) (- 0 (my-parse (second xs)))]
            [(equal? '! op) (fact (my-parse (second xs)))])
          (cond 
            [(equal? '+ op) (+ (my-parse (second xs)) (my-parse (third xs)))]
            [(equal? '* op) (* (my-parse (second xs)) (my-parse (third xs)))]
            [(equal? '- op) (- (my-parse (second xs)) (my-parse (third xs)))]
            [(equal? '^ op) (expt (my-parse (second xs)) (my-parse (third xs)))]
            [(equal? '/ op) (/ (my-parse (second xs)) (my-parse (third xs)))])))]))

; ==============================================

(define (eval-op op)
  (type-case Op op
    [(op-add) +]
    [(op-sub) -]
    [(op-mul) *]
    [(op-div) /]
    [(op-pow) expt]))

(define (eval-uop op)
  (type-case Uop op
    [(op-fact) fact]
    [(op-inv) inv]))

(define (eval e)
  (type-case Exp e
    [(exp-number n)    n]
    [(exp-uop op e1)
      ((eval-uop op) (eval e1))]
    [(exp-op op e1 e2)
      ((eval-op op) (eval e1) (eval e2))]))