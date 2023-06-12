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

;; parser -----------------------------------------------

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
    [(s-exp-match? `{define {ANY ...} for ANY} s)
      (defE 
        (map parse (s-exp->list (second (s-exp->list s))))
        (parse (fourth (s-exp->list s))))]
    [else 
      (begin 
        (display s)
        (error 'parse "invalid input"))]))

(define (parse-op [op : Symbol]) : Op
  (cond
    [(eq? op '+) (add)]
    [(eq? op '-) (sub)]
    [(eq? op '*) (mul)]
    [(eq? op '<=) (leq)]
    [else (error 'parse "unknown operator")]))

(module+ test
  (test (parse `{define {[fun fact (n) = {ifz n then 1 else {n * {fact ({n - 1})}}}]} for {fact (5)}})
        (numE 3)))

;; env ----------------------------------------------------

(define-type Item
  (valI [v : Value])
  (funcI [args : (Listof Symbol)] [e : Exp] [env : Env]))

(define-type Binding
  (bind [name : Symbol]
        [val : Item])) 

(define-type-alias Env (Listof Binding))

(define mt-env empty)
(define (extend-env [env : Env] [x : Symbol] [e : Item]) : Env
  (cons (bind x e) env))

(define (lookup-env [n : Symbol] [env : Env]) : Item
  (type-case (Listof Binding) env
    [empty (error 'lookup "unbound variable")]
    [(cons b rst-env) (cond
                        [(eq? n (bind-name b))
                          (bind-val b)]
                        [else (lookup-env n rst-env)])]))

(define (<= a b)
  (if (or (< a b) (= a b))
    0
    1))

(define (op->proc [op : Op]) : (Value Value -> Value)
  (type-case Op op
    [(add) +]
    [(sub) -]
    [(mul) *]
    [(leq) <=]))                    

(define (eval [e : Exp] [env : Env]) : Value
  (type-case Exp e
    [(numE n) n]
    [(opE l o r) ((op->proc o) (eval l env) (eval r env))]
    [(ifE b t f)
      (if (= 0 (eval b env))
        (eval t env)
        (eval f env))]
    [(varE x)
     (valI-v (lookup-env x env))]
    [(letE x e1 e2)
      (eval e2 (extend-env env x (valI (eval e1 env))))]
    [(funE f x e)
      32]
    [(appE f e2)
     3]
    [(defE e1 e2)
      ; (begin 
      ;   (foreach (lambda (x) (eval x env)) e1)
      ;   (eval e2 env))
        2]))

(define (apply [f : Func-closure] [args : (Listof Value)]) : Value
  (type-case Func-closure f
    [(func-closure xs e env)
     (eval-exp e (foldr (lambda (x env) (extend-env env (fst x) (snd x)))
                        env
                        (map2 pair xs args)))]))