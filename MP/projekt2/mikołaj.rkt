#lang racket
(require data/heap)
(require racket/trace)
(provide sim? wire?
         (contract-out
          [make-sim        (-> sim?)]
          [sim-wait!       (-> sim? positive? void?)]
          [sim-time        (-> sim? real?)]
          [sim-add-action! (-> sim? positive? (-> any/c) void?)]

          [make-wire       (-> sim? wire?)]
          [wire-on-change! (-> wire? (-> any/c) void?)]
          [wire-value      (-> wire? boolean?)]
          [wire-set!       (-> wire? boolean? void?)]

          [bus-value (-> (listof wire?) natural?)]
          [bus-set!  (-> (listof wire?) natural? void?)]

          [gate-not  (-> wire? wire? void?)]
          [gate-and  (-> wire? wire? wire? void?)]
          [gate-nand (-> wire? wire? wire? void?)]
          [gate-or   (-> wire? wire? wire? void?)]
          [gate-nor  (-> wire? wire? wire? void?)]
          [gate-xor  (-> wire? wire? wire? void?)]

          [wire-not  (-> wire? wire?)]
          [wire-and  (-> wire? wire? wire?)]
          [wire-nand (-> wire? wire? wire?)]
          [wire-or   (-> wire? wire? wire?)]
          [wire-nor  (-> wire? wire? wire?)]
          [wire-xor  (-> wire? wire? wire?)]

          [flip-flop (-> wire? wire? wire? void?)]))

(struct sim ([time #:mutable] [actions-queue #:mutable]) #:transparent)
(struct wire ([value #:mutable] [actions-queue #:mutable] sim) #:transparent)

(define (sort e1 e2) ;sortowanie po czasach danych zdarzen
  (if (<= (car e1) (car e2))
      #t
      #f))

(define (make-sim) ;tworzenie symulacji
  (sim 0 (make-heap sort)))

(define (make-wire sim) ;tworzenie przewodow (na domyslnych wartosciach zmiennych)
  (wire #f null sim))

(define (call-each procs) ; wywolywanie procedur po kolei
  (if (null? procs)
      (void)
      (begin
        ((car procs))
        (call-each (cdr procs)))))

(define (sim-wait! sim time)
  (if (and (not (equal? 0 (heap-count (sim-actions-queue sim)))) (<= (car (heap-min (sim-actions-queue sim))) (+ time (sim-time sim)))) ;jesli w kopcu sa elementy a czas ktory uplynal <= czas symulacji
      (let ([first-action (heap-min (sim-actions-queue sim))]) ;bierzemy 1 akcje z kopca
        (begin
          (define tmp (- (+ time (sim-time sim)) (car first-action))) ;powiekszamy time o czas symulacji i pomniejszamy o czas 1 akcji
          (heap-remove-min! (sim-actions-queue sim)) ;usuwamy akcje z kopca
          (set-sim-time! sim (car first-action)) ;ustawiamy czas symulacji na czas tej akcji
          ((cdr first-action)) ;wykonujemy akcje
          (sim-wait! sim tmp))) ;wywolujemy rekurencyjnie dla sim i tmp
      (set-sim-time! sim (+ time (sim-time sim))))) ;jesli if nie jest spelniony, po prostu dodajemy czas

(define (sim-add-action! sim time proc) ;dodanie akcji do kolejki (kopca)
  (heap-add! (sim-actions-queue sim) (cons (+ time (sim-time sim)) proc)))

(define (wire-on-change! wire action) ;dodanie akcji wykonywanych przy kazdej zmianie wartosci
  (begin
    (set-wire-actions-queue! wire (append (wire-actions-queue wire) (list action))) ;samo dodanie akcji
    (action))) ;natychmiastowe wywolanie

(define (wire-set! wire val) ;ustawienie wartosci przewodu
  (if (not (equal? val (wire-value wire))) ;jesli sie rozni od aktualnej
      (begin
        (set-wire-value! wire val) ;to ustawic
        (call-each (wire-actions-queue wire))) ;i od razu wywolac wszystkie akcje
      (void))) ;jesli nie to nie robic nic

(define (bus-set! wires value)
  (match wires
    ['() (void)]
    [(cons w wires)
     (begin
       (wire-set! w (= (modulo value 2) 1))
       (bus-set! wires (quotient value 2)))]))

(define (bus-value ws)
  (foldr (lambda (w value) (+ (if (wire-value w) 1 0) (* 2 value)))
         0
         ws))

(define (gate-not out in) ;1-arg bramka not
  (define (not-action)
    (sim-add-action! (wire-sim out) 1 (lambda () (wire-set! out (not (wire-value in)))))) ;definiujemy akcje not
  (wire-on-change! in not-action)) ;wykonujemy ja na przewodzie in

(define (gate-2arg out in1 in2 time f) ;ogolna bramka 2-argumentowa
  (define (action)
    (sim-add-action! (wire-sim out) time (lambda () (wire-set! out (f (wire-value in1) (wire-value in2))))))
  (wire-on-change! in1 action)
  (wire-on-change! in2 action))

(define (my-and a b) ;opakowane operatory logiczne
  (and a b)) 

(define (my-or a b)
  (or a b))

(define (my-nand a b)
  (nand a b))

(define (my-nor a b)
  (nor a b))

(define (my-xor a b)
  (xor a b))

(define (gate-and out in1 in2) ;bramki 2-arg wykorzystujace ogolna bramke i operatory
  (gate-2arg out in1 in2 1 my-and))

(define (gate-or out in1 in2)
  (gate-2arg out in1 in2 1 my-or))

(define (gate-nand out in1 in2)
  (gate-2arg out in1 in2 1 my-nand))

(define (gate-nor out in1 in2)
  (gate-2arg out in1 in2 1 my-nor))

(define (gate-xor out in1 in2)
  (gate-2arg out in1 in2 2 my-xor))

#;(define (.gate-and out in1 in2)
  (define (and-action)
    (sim-add-action! (wire-sim out) 1 (lambda () (wire-set! out (and (wire-value in1) (wire-value in2))))))
  (wire-on-change! in1 and-action)
  (wire-on-change! in2 and-action))

#;(define (.gate-or out in1 in2)
  (define (or-action)
    (sim-add-action! (wire-sim out) 1 (lambda () (wire-set! out (or (wire-value in1) (wire-value in2))))))
  (wire-on-change! in1 or-action)
  (wire-on-change! in2 or-action))

#;(define (.gate-nand out in1 in2)
  (define (nand-action)
    (sim-add-action! (wire-sim out) 1 (lambda () (wire-set! out (nand (wire-value in1) (wire-value in2))))))
  (wire-on-change! in1 nand-action)
  (wire-on-change! in2 nand-action))

#;(define (.gate-nor out in1 in2)
  (define (nor-action)
    (sim-add-action! (wire-sim out) 1 (lambda () (wire-set! out (nor (wire-value in1) (wire-value in2))))))
  (wire-on-change! in1 nor-action)
  (wire-on-change! in2 nor-action))

#;(define (.gate-xor out in1 in2)
  (define (xor-action)
    (sim-add-action! (wire-sim out) 2 (lambda () (wire-set! out (xor (wire-value in1) (wire-value in2))))))
  (wire-on-change! in1 xor-action)
  (wire-on-change! in2 xor-action))

(define (wire-not in) ;przewody oparte na bramkach
  (define out (make-wire (wire-sim in)))
  (gate-not out in)
  out)

(define (wire-and in1 in2)
  (define out (make-wire (wire-sim in1)))
  (gate-and out in1 in2)
  out)

(define (wire-or in1 in2)
  (define out (make-wire (wire-sim in1)))
  (gate-or out in1 in2)
  out)

(define (wire-nand in1 in2)
  (define out (make-wire (wire-sim in1)))
  (gate-nand out in1 in2)
  out)

(define (wire-nor in1 in2)
  (define out (make-wire (wire-sim in1)))
  (gate-nor out in1 in2)
  out)

(define (wire-xor in1 in2)
  (define out (make-wire (wire-sim in1)))
  (gate-xor out in1 in2)
  out)

(define (flip-flop out clk data)
  (define sim (wire-sim data))
  (define w1  (make-wire sim))
  (define w2  (make-wire sim))
  (define w3  (wire-nand (wire-and w1 clk) w2))
  (gate-nand w1 clk (wire-nand w2 w1))
  (gate-nand w2 w3 data)
  (gate-nand out w1 (wire-nand out w3)))

;testy sprawdzajace co zwracaja procedury
;(trace wire-xor)
(trace flip-flop)
(trace make-wire)
(trace gate-xor)
(trace wire-xor)


