#lang plait

(define-type-alias Value Number)

(define (run [s : S-Exp]) : Value
  (error 'run "not implemented"))

(define-type Op
  (add) (sub) (mul) (leq))

(define-type Exp
  (numE [n : Number])
  (opE  [l : Exp] [op : Op] [r : Exp])
  (ifE  [b : Exp] [t : Exp] [f : Exp])
  (varE [x : Symbol])
  (letE [x : Symbol] [e1 : Exp] [e2 : Exp])
  (funE [f : Symbol] [x : (Listof Symbol)] [e : Exp])
  (appE [f : Symbol] [e : (Listof Exp)])
  (defE [b : (Listof Exp)] [e : Exp]))


(define (parse [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    [(s-exp-match? `{ifz ANY than ANY else ANY} s)
     (ifE (parse (second (s-exp->list s)))
          (parse (third (s-exp->list s)))
          (parse (fourth (s-exp->list s))))]
    [(s-exp-match? `SYMBOL s)
     (varE (s-exp->symbol s))]
    [(s-exp-match? `{let SYMBOL ANY ANY} s)
     (letE (s-exp->symbol (second (s-exp->list s)))
           (parse (third (s-exp->list s)))
           (parse (fourth (s-exp->list s))))]
    [(s-exp-match? `{ANY SYMBOL ANY} s)
      (opE 
        (parse (first (s-exp->list s)))
        (parse-op (s-exp->symbol (second (s-exp->list s))))
        (parse (third (s-exp->list s))))]
    [(s-exp-match? `{SYMBOL {ANY ...}} s)
      (appE 
        (s-exp->symbol (first (s-exp->list s)))
        (map parse (s-exp->list (second (s-exp->list s)))))]
    [(s-exp-match? `{fun SYMBOL {SYMBOL ...} = ANY} s)
      (funE  
        (s-exp->symbol (second (s-exp->list s)))
        (map s-exp->symbol (s-exp->list (third (s-exp->list s))))
        (parse (list-ref (s-exp->list s) 4)))]
    [else (error 'parse "invalid input")]))

(define (parse-op [op : Symbol]) : Op
  (cond
    [(eq? op '+) (add)]
    [(eq? op '-) (sub)]
    [(eq? op '*) (mul)]
    [(eq? op '<=) (leq)]
    [else (error 'parse "unknown operator")]))

(define-type Binding
  (bind [name : Symbol]
        [val : Exp])) ; val trzyma funkcje

(define-type-alias Env (Listof Binding))

(define mt-env empty)
(define (extend-env [env : Env] [x : Symbol] [e : Exp]) : Env
  (cons (bind x e) env))
(define (lookup-env [n : Symbol] [env : Env]) : Value
  (type-case (Listof Binding) env
    [empty (error 'lookup "unbound variable")]
    [(cons b rst-env) (cond
                        [(eq? n (bind-name b))
                         (eval (bind-val b) env)]
                        [else (lookup-env n rst-env)])]))

(define (eval [e : Exp] [env : Env]) : Value
  (type-case Exp e
    [(numE n) (numV n)]
    [(opE o l r) ((op->proc o) (eval l env) (eval r env))]
    [(ifE b l r)
     (type-case Value (eval b env)
       [(boolV v)
        (if v (eval l env) (eval r env))]
       [else
        (error 'eval "type error")])]
    [(varE x)
     (lookup-env x env)]
    [(letE x e1 e2)
       (eval e2 (extend-env env x e1))]
    [(funE f x e)
      ()]
    [(appE e1 e2)
     (apply (eval e1 env) e2 env)])) ; zwracamy funkcje na wartość