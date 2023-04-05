#lang racket

(define-struct column-info (name type) #:transparent)

(define-struct table (schema rows) #:transparent)

(define cities
    (table
        (list 
            (column-info 'city 'string)
            (column-info 'country 'string)
            (column-info 'area 'number)
            (column-info 'capital 'boolean))
        (list 
            (list "Wroclaw" "Poland" 293 #f)
            (list "Warsaw" "Poland" 517 #t)
            (list "Poznan" "Poland" 262 #f)
            (list "Berlin" "Germany" 892 #t)
            (list "Munich" "Germany" 310 #f)
            (list "Paris" "France" 105 #t)
            (list "Rennes" "France" 50 #f))))

(define (equal-type? type symbol)
    (cond 
            [(equal? symbol 'string) (string? type)]
            [(equal? symbol 'number) (number? type)]
            [(equal? symbol 'boolean) (boolean? type)]
            [(equal? symbol 'symbol) (symbol? type)]))

(define (get-right-idx sym tab)
    (define (itr i t)
        (if (null? t)
            null
            (if (member (column-info-name (car t)) sym)
                (cons i (itr (add1 i) (cdr t)))
                (itr (add1 i) (cdr t)))))
    (itr 0 (table-schema tab)))

(define (get-idx sym tab)
    (define (itr i t)
        (if (null? t)
            -1
            (if (equal? (column-info-name (car t)) sym)
                i
                (itr (add1 i) (cdr t)))))
    (itr 0 (table-schema tab)))

(define (get-ord-idx sym tab)
    (define (itr i)
        (if (null? i)
            null
            (cons (get-idx (car i) tab) (get-ord-idx (cdr i) tab))))
    (itr sym))

(define test 
    (list
        (list 1 2 3 4 5)
        (list 6 7 8 9 10)
    ))

(define (select-elems idx tab)
    (define (itr i idt diff t)
        (if (= i diff)
            '()
            (if (member i idt)
                (cons (list-ref t i) (itr (add1 i) idt diff t))
                (itr (add1 i) idt diff t))))
    (itr 0 idx (length tab) tab))

(define (select-elems2 idx tab)
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
  (itr (select-elems2 lst a) (select-elems2 lst b)))

(define (test-sort list)
  (sort list type-comp))

(define (table-sort cols tab)
  (define idx (get-ord-idx cols tab))
  (make-table (table-schema tab) (sort (table-rows tab) (lambda (a b) (multi-type-comp a b idx))))) 

(define-struct and-f (l r))
(define-struct or-f (l r))
(define-struct not-f (e))
(define-struct eq-f (name val))
(define-struct eq2-f (name name2))
(define-struct lt-f (name val))

(define (intersection lst1 lst2)
  (define (itr l)
    (if (not (check-duplicates l))
      '()
      (cons (check-duplicates l) (itr (remove (check-duplicates l) l)))))
  (itr (append lst1 lst2)))

(define (union lst1 lst2)
  (remove-duplicates (append lst1 lst2)))

(define (select-values name val table)
  (define idx (get-idx name table))
  (define (itr l)
    (if (null? l)
      l
      (if (equal? val (list-ref (car l) idx))
        (cons (car l) (itr (cdr l)))
        (itr (cdr l)))))
  (itr (table-rows table))) 

(define (select-lower-values name val table)
  (define idx (get-idx name table))
  (define (itr l)
    (if (null? l)
      l
      (if (type-comp (list-ref (car l) idx) val)
        (cons (car l) (itr (cdr l)))
        (itr (cdr l)))))
  (itr (table-rows table))) 

(define (select-equal-values name name2 table)
  (define idx (get-idx name table))
  (define idx2 (get-idx name2 table))
  (define (itr l)
    (if (null? l)
      l
      (if (equal? (list-ref (car l) idx2) (list-ref (car l) idx))
        (cons (car l) (itr (cdr l)))
        (itr (cdr l)))))
  (itr (table-rows table)))

(define (form-interpreter form table)
    (cond 
        [(and-f? form) (intersection (form-interpreter (and-f-l form) table) (form-interpreter (and-f-r form) table))]
        [(or-f? form) (union (form-interpreter (or-f-l form) table) (form-interpreter (or-f-r form) table))]
        [(not-f? form) (remove* (form-interpreter (not-f-e form) table) (table-rows table))]
        [(eq-f? form) (select-values (eq-f-name form) (eq-f-val form) table)]
        [(eq2-f? form) (select-equal-values (eq2-f-name form) (eq2-f-name2 form) table)]
        [(lt-f? form) (select-lower-values (lt-f-name form) (lt-f-val form) table)]))


(define (table-select form table)
  (make-table (table-schema table) (form-interpreter form table)))