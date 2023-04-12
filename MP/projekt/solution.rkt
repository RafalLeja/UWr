#lang racket

(provide (struct-out column-info)
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

;--- funkcje pomocnicze

;funkcja sprawdzająca typ
(define (equal-type? type symbol)
  (cond 
          [(equal? symbol 'string) (string? type)]
          [(equal? symbol 'number) (number? type)]
          [(equal? symbol 'boolean) (boolean? type)]
          [(equal? symbol 'symbol) (symbol? type)]))

;funkcja sprawdzająca poprawność wiersza
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

;znajdowanie pierwszego indeksu symbolu
(define (find-idx sym tab)
  (define (itr i t)
      (if (null? t)
          -1
          (if (equal? (column-info-name (car t)) sym)
              i
              (itr (add1 i) (cdr t)))))
  (itr 0 (table-schema tab)))

;znajdowanie indeksów kolumn
(define (get-ordered-idx sym tab)
  (define (itr i)
      (if (null? i)
          null
          (cons (find-idx (car i) tab) (get-ordered-idx (cdr i) tab))))
  (itr sym))

;filtrowanie listy przy pomocy listy indeksów
(define (select-elems idx tab)
  (define (itr i)
      (if (null? i)
          null
          (cons (list-ref tab (car i)) (itr (cdr i)))))
  (itr idx))

;porównywanie dla dowolnego typu
(define (type-comp a b)
  (cond 
          [(string? a) (string<? a b)]
          [(integer? a) (< a b)]
          [(boolean? a) (if (boolean=? a b)
                          #f
                          b)]
          [(symbol? a) (symbol<? a b)]))

;funkcja porównawcza
(define (multi-type-comp a b lst)
  (define (itr a_col b_col)
    (if (null? a_col)
      #f
      (if (type-comp (car a_col) (car b_col))
        #t
        (itr (cdr a_col) (cdr b_col)))))
  (itr (select-elems lst a) (select-elems lst b)))

;część wspólna zbiorów
(define (intersection lst1 lst2)
  (define (itr l)
    (if (not (check-duplicates l))
      '()
      (cons (check-duplicates l) (itr (remove (check-duplicates l) l)))))
  (itr (append lst1 lst2)))

;suma zbiorów
(define (union lst1 lst2)
  (remove-duplicates (append lst1 lst2)))

;znajdz pierwszy indeks
(define (get-idx sym tab)
  (define (itr i t)
    (if (null? t)
      -1
      (if (equal? (column-info-name (car t)) sym)
        i
        (itr (add1 i) (cdr t)))))
  (itr 0 (table-schema tab)))

;zwróć wartości równe val
(define (select-values name val table)
  (define idx (get-idx name table))
  (define (itr l)
    (if (null? l)
      l
      (if (equal? val (list-ref (car l) idx))
        (cons (car l) (itr (cdr l)))
        (itr (cdr l)))))
  (itr (table-rows table)))

;zwróć wiersze o równych kolumnach
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

;zwróć wiersze mniejsze niż val
(define (select-lower-values name val table)
  (define idx (get-idx name table))
  (define (itr l)
    (if (null? l)
      l
      (if (type-comp (list-ref (car l) idx) val)
        (cons (car l) (itr (cdr l)))
        (itr (cdr l)))))
  (itr (table-rows table)))

;łączenie wszystkich wierszy tab2 z wierszem tab1
(define (cross-join tab1 tab2)
  (define (itr t)
    (if (null? t)
      t 
      (cons 
        (append tab1 (car t))
        (itr (cdr t)))))
  (itr tab2))

;usuwanie duplikatów i błędnych wierszy
(define (unduplicate lst1)
  (define (itr l)
    (if (null? l)
      l 
      (if (check-duplicates (car l))
        (cons (remove-duplicates (car l)) (itr (cdr l)))
        (itr (cdr l)))))
  (itr lst1))

; Wstawianie

(define (table-insert row tab)
  (if (table-schema-check row tab)
        (make-table (table-schema tab) (append (table-rows tab) (list row)))
        (error "złe typy danych"))
  )

; Projekcja

(define (table-project cols tab)
  (define idx 
        (get-ordered-idx cols tab))
    (make-table (select-elems idx (table-schema tab)) (map (lambda (x) (select-elems idx x)) (table-rows tab))))

; Sortowanie

(define (table-sort cols tab)
  (define idx (get-ordered-idx cols tab))
  (make-table (table-schema tab) (sort (table-rows tab) (lambda (a b) (multi-type-comp a b idx)))))


; Selekcja

(define-struct and-f (l r))
(define-struct or-f (l r))
(define-struct not-f (e))
(define-struct eq-f (name val))
(define-struct eq2-f (name name2))
(define-struct lt-f (name val))

(define (table-select form tab)
  (define (form-interpreter form table)
    (cond 
      [(and-f? form) (intersection (form-interpreter (and-f-l form) table) (form-interpreter (and-f-r form) table))]
      [(or-f? form) (union (form-interpreter (or-f-l form) table) (form-interpreter (or-f-r form) table))]
      [(not-f? form) (remove* (form-interpreter (not-f-e form) table) (table-rows table))]
      [(eq-f? form) (select-values (eq-f-name form) (eq-f-val form) table)]
      [(eq2-f? form) (select-equal-values (eq2-f-name form) (eq2-f-name2 form) table)]
      [(lt-f? form) (select-lower-values (lt-f-name form) (lt-f-val form) table)]))
  (make-table (table-schema tab) (form-interpreter form tab)))

; Zmiana nazwy

(define (table-rename col ncol tab)
  (define (itr t)
        (if (equal? col (column-info-name (car t)))
            (cons (make-column-info ncol (column-info-type (car t))) (cdr t))
            (cons (car t) (itr (cdr t)))))
    (make-table (itr (table-schema tab)) (table-rows tab)))

; Złączenie kartezjańskie

(define (table-cross-join tab1 tab2)
  (make-table 
    (append (table-schema tab1) (table-schema tab2))
    (append-map (lambda (x) (cross-join x (table-rows tab2))) (table-rows tab1))))

; Złączenie

(define (table-natural-join tab1 tab2)
  (define table (table-cross-join tab1 tab2))
  (define schema (remove-duplicates (table-schema table)))
  (make-table
    schema
    (unduplicate (table-rows table))))

