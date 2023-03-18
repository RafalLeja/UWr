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

(define (table-schema-check row tab)
    (define (itr col)
        (cond 
            [(equal? (cdr (car col)) 'string) ()])))

; (define (table-insert row tab)
;     (cond [(equal? (cdr row) (table-schema tab))]))