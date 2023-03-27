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

(define (table-schema-check row tab)
    (define (itr r ci)
        (if (null? ci)
            #t
            (if (equal-type? (car r) (column-info-type (car ci)))
                (itr (cdr r) (cdr ci))
                #f)))
    (itr row (table-schema tab)))

; (define (table-insert row tab)
;     (cond [(equal? (cdr row) (table-schema tab))]))