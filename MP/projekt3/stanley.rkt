#lang plait

;; abstract syntax

(define-type Prog
  (defineE [fs : (Listof Func)] [e : Exp]))

(define-type Func
  (funcE [id : Symbol] [args : (Listof Symbol)] [e : Exp]))

(define-type Exp
  (numE [n : Number])
  (varE [x : Symbol])
  (opE  [e1 : Exp] [op : Op] [e2 : Exp])
  (ifzE [e0 : Exp] [e1 : Exp] [e2 : Exp])
  (letE [x : Symbol] [e1 : Exp] [e2 : Exp])
  (appE [f : Symbol] [args : (Listof Exp)]))

(define-type Op
  (add) (sub) (mul) (leq))

;; parse

(define (parse [s : S-Exp]) : Prog
  (cond
    [(s-exp-match? `{define {ANY ...} for ANY} s)
     (defineE (let ([fs (map parse-func (s-exp->list (second (s-exp->list s))))])
                (if (unique? (map funcE-id fs))
                    fs
                    (error 'parse "duplicate function names")))
       (parse-exp (fourth (s-exp->list s))))]
    [else (error 'parse "syntax error")]))

(define (parse-func [s : S-Exp]) : Func
  (cond
    [(s-exp-match? `[fun SYMBOL (SYMBOL ...) = ANY] s)
     (funcE (s-exp->symbol (second (s-exp->list s)))
            (let ([args (map s-exp->symbol (s-exp->list (third (s-exp->list s))))])
              (if (unique? args)
                  args
                  (error 'parse-func "duplicate argument names")))
            (parse-exp (list-ref (s-exp->list s) 4)))]
    [else (error 'parse-func "syntax-error")]))

(define (parse-exp [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    [(s-exp-match? `SYMBOL s)
     (varE (s-exp->symbol s))]
    [(s-exp-match? `{ifz ANY then ANY else ANY} s)
     (ifzE (parse-exp (second (s-exp->list s)))
           (parse-exp (fourth (s-exp->list s)))
           (parse-exp (list-ref (s-exp->list s) 5)))]
    [(s-exp-match? `{let SYMBOL be ANY in ANY} s)
     (letE (s-exp->symbol(second (s-exp->list s)))
           (parse-exp (fourth (s-exp->list s)))
           (parse-exp (list-ref (s-exp->list s) 5)))]
    [(s-exp-match? `{ANY SYMBOL ANY} s)
     (opE (parse-exp (first (s-exp->list s)))
          (parse-op (s-exp->symbol (second (s-exp->list s))))
          (parse-exp (third (s-exp->list s))))]
    [(s-exp-match? `{SYMBOL (ANY ...)} s)
     (appE (s-exp->symbol (first (s-exp->list s)))
           (map parse-exp (s-exp->list (second (s-exp->list s)))))]
    [else (error 'parse-exp "syntax error")]))

(define (parse-op [s : Symbol]) : Op
  (cond
    [(eq? s '+) (add)]
    [(eq? s '-) (sub)]
    [(eq? s '*) (mul)]
    [(eq? s '<=) (leq)]
    [else (error 'parse-op (string-append "unknown operator: " (symbol->string s)))]))

(define (unique? [xs : (Listof Symbol)]) : Boolean
  (type-case (Listof Symbol) xs
    [empty #t]
    [(cons x xs)
     (if (member x xs)
         #f
         (unique? xs))]))

;; value

(define-type-alias Value Number)

(define-type Func-closure
  (func-closure [args : (Listof Symbol)] [e : Exp] [env : Env]))

;; environment

(define-type Storable
  (valS  [v : Value])
  (funcS [f : Func-closure])
  (undefS))

(define-type Binding
  (bind [id : Symbol] [ref : (Boxof Storable)]))

(define-type-alias Env (Listof Binding))

(define empty-env empty)

(define (extend-env-undef [env : Env] [id : Symbol]) : Env
  (cons (bind id (box (undefS))) env))

(define (extend-env [env : Env] [x : Symbol] [v : Value]) : Env
  (cons (bind x (box (valS v))) env))

(define (find [env : Env] [id : Symbol]) : (Boxof Storable)
  (type-case Env env
    [empty (error 'find (string-append "unbound variable: " (symbol->string id)))]
    [(cons b env)
     (cond
       [(eq? (bind-id b) id) (bind-ref b)]
       [else (find env id)])]))

(define (lookup-env-var [env : Env] [id : Symbol]) : Value
  (type-case Storable (unbox (find env id))
    [(valS v) v]
    [(funcS f) (error 'lookup-env-var
                      (string-append "not a variable - is a function: "
                                     (symbol->string id)))]
    [(undefS) (error 'lookup-env-var (string-append "undefined variable: "
                                                    (symbol->string id)))]))

(define (lookup-env-func [env : Env] [id : Symbol]) : Func-closure
  (type-case Storable (unbox (find env id))
    [(funcS f) f]
    [(valS v) (error 'lookup-env-func
                     (string-append "not a function - is a variable: "
                                    (symbol->string id)))]
    [(undefS) (error 'lookup-env-func (string-append "undefined variable: "
                                                     (symbol->string id)))]))

(define (update-env! [env : Env] [id : Symbol] [args : (Listof Symbol)] [e : Exp] [envf : Env]) : Void
  (set-box! (find env id) (funcS (func-closure args e envf))))

;; evaluation

;; operators

(define (op->proc [op : Op]) : (Value Value -> Value)
  (type-case Op op
    [(add) +]
    [(sub) -]
    [(mul) *]
    [(leq) (lambda (x y) (if (<= x y) 0 69))]))

;; eval

(define (eval [p : Prog]) : Value
 (type-case Prog p
   [(defineE fs e)
    (let ([new-env (foldr (lambda (f env) (extend-env-undef env (funcE-id f)))
                        empty-env
                        fs)])
      (begin
        (foldr (lambda (f fs) (type-case Func f
                                [(funcE id args e)
                                 (update-env! new-env id args e new-env)]))
               (void)
               fs)
        (eval-exp e new-env)))]))

(define (eval-exp [e : Exp] [env : Env]) : Value
  (type-case Exp e
    [(numE n) n]
    [(varE x) (lookup-env-var env x)]
    [(opE e1 op e2) ((op->proc op) (eval-exp e1 env) (eval-exp e2 env))]
    [(ifzE e0 e1 e2)
     (if (= (eval-exp e0 env) 0)
         (eval-exp e1 env)
         (eval-exp e2 env))]
    [(letE x e1 e2)
     (eval-exp e2 (extend-env env x (eval-exp e1 env)))]
    [(appE f args)
     (apply (lookup-env-func env f) (map (lambda (e) (eval-exp e env)) args))]))

(define (apply [f : Func-closure] [args : (Listof Value)]) : Value
  (type-case Func-closure f
    [(func-closure xs e env)
     (eval-exp e (foldr (lambda (x env) (extend-env env (fst x) (snd x)))
                        env
                        (map2 pair xs args)))]))

;;run 

(define (run [s : S-Exp]) : Value
  (eval (parse s)))

#|
;; tests
#;(trace eval-exp)

(module+ test
  (print-only-errors #t))

(module+ test
  (test (run `{define {[fun fact (n) =
                            {ifz n
                                 then 1
                                 else {n * {fact ({n - 1})}}}]}
                for
                {fact (6)}})
        720)
  (test (run `{define
                {[fun even (n) = {ifz n
                                      then 0
                                      else {odd ({n - 1})}}]
                 [fun odd (n) = {ifz n
                                     then 69
                                     else {even ({n - 1})}}]}
                for
                {odd (1023)}})
        0))
;; |#