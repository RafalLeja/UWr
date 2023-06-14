#lang plait

(define-type-alias Value Number)

(define (run [s : S-Exp]) : Value
  (eval (parse s) mt-env))

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
    [(s-exp-match? `{ifz ANY then ANY else ANY} s)
     (ifE (parse (second (s-exp->list s)))
          (parse (fourth (s-exp->list s)))
          (parse (list-ref (s-exp->list s) 5)))]
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
        (let ([funcs (map parse (s-exp->list (second (s-exp->list s))))])
          (if (check-unique (map funE-f funcs))
            funcs
            (error 'syntax "duplicate function names")))
        (parse (fourth (s-exp->list s))))]
    [else 
      (begin 
        (display s)
        (error 'parse "invalSd input"))]))

(define (check-unique xs) : Boolean
  (cond 
    [(empty? xs) #t]
    [(member (first xs) (rest xs)) #f]
    [else (check-unique (rest xs))]))

(define (parse-op [op : Symbol]) : Op
  (cond
    [(eq? op '+) (add)]
    [(eq? op '-) (sub)]
    [(eq? op '*) (mul)]
    [(eq? op '<=) (leq)]
    [else (error 'parse "unknown operator")]))

(module+ test
  (test (parse `{ifz n then 1 else {n * {fact {{n - 1}}}}})
        (ifE (varE 'n) (numE 1) (opE (varE 'n) (mul) (appE 'fact (list (opE (varE 'n) (sub) (numE 1))))))))

;; env ----------------------------------------------------

(define-type Item
  (funcI [args : (Listof Symbol)] [e : Exp] [env : Env]))

(define-type Storable
  (valS [v : Value])
  (funcS [f : Item])
  (undefS))

(define-type Binding
  (bind [name : Symbol]
        [ref : (Boxof Storable)]))

(define-type-alias Env (Listof Binding))

(define mt-env empty)

(define (extend-env-undef [env : Env] [x : Symbol]) : Env
  (cons (bind x (box (undefS))) env))

(define (extend-env [env : Env] [x : Symbol] [v : Storable]) : Env
  (cons (bind x (box v)) env))

(define (find-var [env : Env] [x : Symbol]) : (Boxof Storable)
  (type-case (Listof Binding) env
    [empty (error 'lookup "unbound variable")]
    [(cons b rst-env) (cond
                        [(eq? x (bind-name b))
                         (bind-ref b)]
                        [else
                         (find-var rst-env x)])]))
  
(define (lookup-env [x : Symbol] [env : Env]) : Value
  (type-case Storable (unbox (find-var env x))
    [(valS v) v]
    [(funcS f) (error 'lookup-env "symbol is a function")]
    [(undefS) (error 'lookup-env "undefined variable")]))

(define (lookup-env-func [x : Symbol] [env : Env]) : Item
  (type-case Storable (unbox (find-var env x))
    [(valS v) (error 'lookup-env "symbol is a variable")]
    [(funcS f) f]
    [(undefS) (error 'lookup-env "undefined variable")]))
   
(define (update-env! [env : Env] [x : Symbol] [v : Storable]) : Void
  (set-box! (find-var env x) v))

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
     (lookup-env x env)]
    [(letE x e1 e2)
      (eval e2 (extend-env env x (valS (eval e1 env))))]
    [(funE f x e)
      32]
    [(appE f e2)
      (apply (lookup-env-func f env) (map (lambda (x) (eval x env)) e2))]
    [(defE e1 e2)
      (let 
        ([def-env 
          (foldr 
            (lambda 
              (f fenv) 
              (extend-env-undef fenv 
                (funE-f f)))
            mt-env
            e1)])
        (begin 
          (foldr 
            (lambda 
              (f fenv) 
                (update-env! def-env 
                  (funE-f f)
                  (funcS 
                    (funcI
                      (funE-x f)
                      (funE-e f)
                    def-env))))
            (void)
            e1)
          (eval e2 def-env)))]))

(define (apply [f : Item] [args : (Listof Value)]) : Value
     (eval (funcI-e f) (foldr (lambda (x env) (extend-env env (fst x) (valS (snd x))))
                        (funcI-env f)
                        (map2 pair (funcI-args f) args))))

