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

(define (project sym tab)
    (define idx 
        (get-right-idx sym tab))
    (make-table (select-elems idx (table-schema tab)) (map (lambda (x) (select-elems idx x)) (table-rows tab))))