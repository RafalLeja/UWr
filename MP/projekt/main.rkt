#lang racket

#;(provide (struct-out column-info)
         (struct-out table)
         (struct-out and-f)
         (struct-out or-f)
         (struct-out not-f)
         (struct-out eq-f)
         (struct-out eq2-f)
         (struct-out lt-f)
         table-insert
         table-project
         table-sort
         table-select
         table-rename
         table-cross-join
         table-natural-join)

(define-struct column-info (name type) #:transparent)

(define-struct table (schema rows) #:transparent)

(define cities
  (table
   (list (column-info 'city    'string)
         (column-info 'country 'string)
         (column-info 'area    'number)
         (column-info 'capital 'boolean))
   (list (list "Wrocław" "Poland"  293 #f)
         (list "Warsaw"  "Poland"  517 #t)
         (list "Poznań"  "Poland"  262 #f)
         (list "Berlin"  "Germany" 892 #t)
         (list "Munich"  "Germany" 310 #f)
         (list "Paris"   "France"  105 #t)
         (list "Rennes"  "France"   50 #f))))

(define countries
  (table
   (list (column-info 'country 'string)
         (column-info 'population 'number))
   (list (list "Poland" 38)
         (list "Germany" 83)
         (list "France" 67)
         (list "Spain" 47))))

(define (empty-table columns) (table columns '()))

; Wstawianie

(define (table-insert row tab)
  (define (equal-type? type symbol)
    (cond 
            [(equal? symbol 'string) (string? type)]
            [(equal? symbol 'number) (number? type)]
            [(equal? symbol 'boolean) (boolean? type)]
            [(equal? symbol 'symbol) (symbol? type)]))
  (define (table-schema-check row tab)
    (define (itr r ci)
        (if (null? ci)
            #t
            (if (equal-type? (car r) (column-info-type (car ci)))
                (itr (cdr r) (cdr ci))
                #f)))
    (if (= (length row) (length (table-schema tab)))
        (itr row (table-schema tab))
        #f))
  (if (table-schema-check row tab)
        (make-table (table-schema tab) (append (table-rows tab) (list row)))
        (error "złe typy danych"))
  )

; Projekcja

(define (table-project cols tab)
  (define (get-right-idx sym idx-tab)
    (define (itr i t)
        (if (null? t)
            null
            (if (member (column-info-name (car t)) sym)
                (cons i (itr (add1 i) (cdr t)))
                (itr (add1 i) (cdr t)))))
    (itr 0 (table-schema idx-tab)))
  (define (select-elems idx elem-tab)
    (define (itr i idt diff t)
        (if (= i diff)
            '()
            (if (member i idt)
                (cons (list-ref t i) (itr (add1 i) idt diff t))
                (itr (add1 i) idt diff t))))
    (itr 0 idx (length elem-tab) elem-tab))
  (define idx 
        (get-right-idx cols tab))
    (make-table (select-elems idx (table-schema tab)) (map (lambda (x) (select-elems idx x)) (table-rows tab))))

; Sortowanie

(define (table-sort cols tab)
  (define (find-idx sym tab)
    (define (itr i t)
        (if (null? t)
            -1
            (if (equal? (column-info-name (car t)) sym)
                i
                (itr (add1 i) (cdr t)))))
    (itr 0 (table-schema tab)))
  (define (get-ordered-idx sym tab)
    (define (itr i)
        (if (null? i)
            null
            (cons (find-idx (car i) tab) (get-ordered-idx (cdr i) tab))))
    (itr sym))
  (define (select-elems idx tab)
    (define (itr i)
        (if (null? i)
            null
            (cons (list-ref tab (car i)) (itr (cdr i)))))
    (itr idx))
  (define (type-comp a b)
    (cond 
            [(string? a) (string<? a b)]
            [(integer? a) (< a b)]
            [(boolean? a) (if (equal? a b)
                            #f
                            a)]
            [(symbol? a) (symbol<? a b)]))
  (define (multi-type-comp a b lst)
    (define (itr a_col b_col)
      (if (null? a_col)
        #f
        (if (type-comp (car a_col) (car b_col))
          #t
          (itr (cdr a_col) (cdr b_col)))))
    (itr (select-elems lst a) (select-elems lst b)))
  (define idx (get-ordered-idx cols tab))
  (make-table (table-schema tab) (sort (table-rows tab) (lambda (a b) (multi-type-comp a b idx)))))


; Selekcja

(define-struct and-f (l r))
(define-struct or-f (l r))
(define-struct not-f (e))
(define-struct eq-f (name val))
(define-struct eq2-f (name name2))
(define-struct lt-f (name val))

#;(define (table-select form tab)
  ;; uzupełnij
  )

; Zmiana nazwy

(define (table-rename col ncol tab)
  (define (itr t)
        (if (equal? col (column-info-name (car t)))
            (cons (make-column-info ncol (column-info-type (car t))) (cdr t))
            (cons (car t) (itr (cdr t)))))
    (make-table (itr (table-schema tab)) (table-rows tab)))

; Złączenie kartezjańskie

#;(define (table-cross-join tab1 tab2)
  ;; uzupełnij
  )

; Złączenie

#;(define (table-natural-join tab1 tab2)
  ;; uzupełnij
  )

