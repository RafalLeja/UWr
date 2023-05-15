#lang plait

(module+ test
  (print-only-errors #t))

;; abstract syntax -------------------------------

(define-type Op
  (add)
  (sub)
  (mul)
  (div))

(define-type Exp
  (numE [n : Number])
  (opE [op : Op] [l : Exp] [r : Exp])
  (op2E [op : Op] [args : (Listof Exp)]))


;; parse ----------------------------------------

(define (parse [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    [(s-exp-match? `{SYMBOL ANY ANY} s)
     (opE (parse-op (s-exp->symbol (first (s-exp->list s))))
          (parse (second (s-exp->list s)))
          (parse (third (s-exp->list s))))]
    [(s-exp-match? `{SYMBOL ANY ...} s)
     [op2E (parse-op (s-exp->symbol (first (s-exp->list s))))
           (map (lambda (x) (parse x)) (rest (s-exp->list s)))]]
    [else (error 'parse "invalid input")]))

(define (parse-op [op : Symbol]) : Op
  (cond
    [(eq? op '+) (add)]
    [(eq? op '-) (sub)]
    [(eq? op '*) (mul)]
    [(eq? op '/) (div)]
    [else (error 'parse "unknown operator")]))
                 
#;(module+ test
  (test (parse `2)
        (numE 2))
  (test (parse `{+ 2 1})
        (opE (add) (numE 2) (numE 1)))
  (test (parse `{* 3 4})
        (opE (mul) (numE 3) (numE 4)))
  (test (parse `{+ {* 3 4} 8})
        (opE (add)
             (opE (mul) (numE 3) (numE 4))
             (numE 8)))
  (test/exn (parse `{{+ 1 2}})
            "invalid input")
  (test/exn (parse `{+ 1})
            "invalid input")
  (test/exn (parse `{^ 1 2})
            "unknown operator"))
  
;; eval --------------------------------------

(define-type-alias Value Number)

(define (op->proc [op : Op]) : (Value Value -> Value)
  (type-case Op op
    [(add) +]
    [(sub) -]
    [(mul) *]
    [(div) /]))

(define (0-arg [op : Op]) : Value
  (type-case Op op
    [(add) 0]
    [(sub) 0]
    [(mul) 1]
    [(div) 1]))

(define (1-arg [op : Op] [v : Value]) : Value
  (type-case Op op
    [(add) v]
    [(sub) (* -1 v)]
    [(mul) v]
    [(div) (/ 1 v)]))

(define (eval [e : Exp]) : Value
  (type-case Exp e
    [(numE n) n]
    [(opE o l r) ((op->proc o) (eval l) (eval r))]
    [(op2E o l)
       (cond
         [(empty? l) (0-arg o)]
         [(= (length l) 1) (1-arg o (eval (first l)))]
         [else (foldl (lambda (el s) ((op->proc o) s (eval el))) (eval (first l)) (rest l))])]))

(define (run [e : S-Exp]) : Value
  (eval (parse e)))

(module+ test
  (test (run `(+ 1 2 3)) 6)
  (test (run `(- 1 2 3 4)) -8)
  (test (run `(- 1 2 3 4 (+ 3 4 5))) -20)
  (test (run `(+ (- 1 2))) -1)
  (test (run `(+)) 0)
  (test (run `(/ 1 2 3)) 1/6)
  (test (run `(* 2)) 2))

;; printer ———————————————————————————————————-

(define (print-value [v : Value]) : Void
  (display v))

(define (main [e : S-Exp]) : Void
  (print-value (eval (parse e))))
