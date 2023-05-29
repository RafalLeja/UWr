#lang racket
(require data/heap)
(require racket/trace)

;STRUKTURY POTRZEBNE W PROGRAMIE
(struct sim ((time #:mutable) (action-queue #:mutable)))
(struct wire ((value #:mutable) (actions #:mutable) sim)) 
(struct action (time proc))
        
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

          [flip-flop (-> wire? wire? wire? void?)]
          ))

;;--------Interfejs symulatora

;;--------Symulacja

(define (<= p1 p2)  ;wlasne mniejsze rownasie dla par czas i akcja
  (if (> (action-time p1) (action-time p2))   ;sortujemy tu po czasie 
    #f
    #t))

(define (make-sim)
  (sim 0 (make-heap <=))) 
 
(define (sim-add-action! sim time proc)
    (heap-add! (sim-action-queue sim) (action (+ (sim-time sim) time) proc)))

(define (make-wire sim)
  (wire #f '() sim))

(define (wire-on-change! wire action)
  (begin (set-wire-actions! wire (cons (wire-actions wire) action)) 
         (action))) 
    ;begin ustawiam wire-actions-queue o action czyli consuje
  ; po dodaniu akcji od razu ja wykonuje

(define (call-all-actions xs)
  (if (empty? xs)
      (void)
      (begin (car xs) 
             (call-all-actions (cdr xs)))))


;pytanie czy tu ten if jest konieczny
(define (wire-set! wire value)
  (if (not (equal? value (wire-value wire)))
    (begin (set-wire-value! wire value) 
         (call-all-actions (wire-actions wire)))
    (void)))


(define (sim-wait! sim time)
  (if (and (> (heap-count (sim-action-queue sim)) 0) (<= (action-time (heap-min (sim-action-queue sim))) (+ (sim-time sim) time)))
    (let [(next-action (heap-min (sim-action-queue sim)))]
      (begin
              (define tmp (- (+ (sim-time sim) time) (action-time next-action)))
               (set-sim-time! sim (action-time next-action)) ; przesuwamy czas
               (heap-remove-min! (sim-action-queue sim)) ; usuwamy akcje
               ((action-proc next-action))
               (sim-wait! sim tmp)))
    (set-sim-time! sim (+ (sim-time sim) time))))


(define (gate-not output input)
  (define (not-action) 
    (sim-add-action! (wire-sim output) 1 (lambda () (wire-set! output (not (wire-value input)))))
  )
  (wire-on-change! input (not-action)))

(define (gate-and output input1 input2)
  (define (and-action) 
    (sim-add-action! (wire-sim output) 1 (lambda () (wire-set! output (and (wire-value input1) (wire-value input2)))))
  )
  (wire-on-change! input1 (and-action))
  (wire-on-change! input2 (and-action)))

(define (gate-nand output input1 input2)
  (define (nand-action) 
    (sim-add-action! (wire-sim output) 1 (lambda () (wire-set! output (nand (wire-value input1) (wire-value input2)))))
  )
  (wire-on-change! input1 (nand-action))
  (wire-on-change! input2 (nand-action)))

(define (gate-or output input1 input2)
  (define (or-action) 
    (sim-add-action! (wire-sim output) 1 (lambda () (wire-set! output (or (wire-value input1) (wire-value input2)))))
  )
  (wire-on-change! input1 (or-action))
  (wire-on-change! input2 (or-action)))

(define (gate-nor output input1 input2)
  (define (nor-action) 
    (sim-add-action! (wire-sim output) 1 (lambda () (wire-set! output (nor (wire-value input1) (wire-value input2)))))
  )
  (wire-on-change! input1 (nor-action))
  (wire-on-change! input2 (nor-action)))

(define (gate-xor output input1 input2)
  (define (xor-action) 
    (sim-add-action! (wire-sim output) 2 (lambda () (wire-set! output (xor (wire-value input1) (wire-value input2)))))
  )
  (wire-on-change! input1 (xor-action))
  (wire-on-change! input2 (xor-action)))


(define (wire-not input)
  (define new-wire (make-wire (wire-sim input)))
  (gate-not new-wire input)
  new-wire)

(define (wire-and input1 input2)
  (define new-wire (make-wire (wire-sim input1)))
  (gate-and new-wire input1 input2)
  new-wire)

(define (wire-nand input1 input2)
  (define new-wire (make-wire (wire-sim input1)))
  (gate-nand new-wire input1 input2)
  new-wire)

(define (wire-or input1 input2)
  (define new-wire (make-wire (wire-sim input1)))
  (gate-or new-wire input1 input2)
  new-wire)

(define (wire-nor input1 input2)
  (define new-wire (make-wire (wire-sim input1)))
  (gate-nor new-wire input1 input2)
  new-wire)

(define (wire-xor input1 input2)
  (define new-wire (make-wire (wire-sim input1)))
  (gate-xor new-wire input1 input2)
  new-wire)


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

(define (flip-flop out clk data)
  (define sim (wire-sim data))
  (define w1  (make-wire sim))
  (define w2  (make-wire sim))
  (define w3  (wire-nand (wire-and w1 clk) w2))
  (gate-nand w1 clk (wire-nand w2 w1))
  (gate-nand w2 w3 data)
  (gate-nand out w1 (wire-nand out w3)))

(trace wire-xor gate-xor sim-add-action! <= )