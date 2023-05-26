#lang racket
(require data/heap)
(require racket/trace)
(provide sim? wire?
         (contract-out
          [make-sim        (-> sim?)]
          [sim-wait!       (-> sim? positive? void?)]
          [sim-time        (-> sim? real?)]

          [sim-heap        (-> sim? heap?)]
          [heap-min        (-> heap? any/c)]
          [action-proc     (-> action? any/c)]

          [sim-add-action! (-> sim? positive? (-> any/c) void?)]

          [make-wire       (-> sim? wire?)]
          [wire-on-change! (-> wire? (-> any/c) void?)]
          [wire-value      (-> wire? boolean?)]

          [wire-actions    (-> wire? list?)]

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

;; actions --------------------------

(struct action (time proc) #:transparent)

;; sim ------------------------------

(struct sim ([time #:mutable] [heap #:mutable]) #:transparent)

(define (make-sim)
  (sim 0 (make-heap (lambda (a b) (<= (action-time a) (action-time b))))))

(define (run-heap heap ct)
  (cond
      [(= (heap-count heap) 0) 
        (void)]
      [(>= ct (action-time (heap-min heap))) 
          ;(print (heap-count heap))
          ((action-proc (heap-min heap))) 
          (heap-remove-min! heap) 
          (run-heap heap ct)]
      [(< ct (action-time (heap-min heap))) 
        (void)]))

(define (sim-wait! s t)
  (let 
    ([ct (+ (sim-time s) t)]
    [heap (sim-heap s)])
    (run-heap heap ct)
    (set-sim-time! s ct)))

(define (sim-add-action! s t proc)
    (heap-add! (sim-heap s) (action t proc)))

;; wire -------------------------------------

(struct wire (sim [value #:mutable] [actions #:mutable]) #:transparent)

(define (make-wire sim)
  (wire sim #f '()))

(define (wire-on-change! w a)
  (a)
  (set-wire-actions! w (append (list a) (wire-actions w))))

(define (wire-set! w v)
  (set-wire-value! w v)
  (for-each (lambda (a) (a)) (wire-actions w)))

;; gate -----------------------------

(define (gate-not out in)
  (let ([sim (wire-sim out)])
    (wire-on-change! in
      (lambda () (sim-add-action! 
        sim 
        (add1 (sim-time sim)) 
        (lambda () (wire-set! out (not (wire-value in)))))))))
  
(define (gate-and out in1 in2)
  (let ([sim (wire-sim out)])
    (wire-on-change! in1
      (lambda () (sim-add-action! 
        sim 
        (add1 (sim-time sim)) 
        (lambda () (
          wire-set! out (and (wire-value in1) (wire-value in2))
          ;print "a"
          )))))
    (wire-on-change! in2
      (lambda () (sim-add-action! 
        sim 
        (add1 (sim-time sim)) 
        (lambda () (wire-set! out (and (wire-value in1) (wire-value in2)))))))))

(define (gate-nand out in1 in2)
  (let ([sim (wire-sim out)])
    (wire-on-change! in1
      (lambda () (sim-add-action! 
        sim 
        (add1 (sim-time sim)) 
        (lambda () (
          wire-set! out (not (and (wire-value in1) (wire-value in2)))
          ; print (not (and (wire-value in1) (wire-value in2)))
          )))))
    (wire-on-change! in2
      (lambda () (sim-add-action! 
        sim 
        (add1 (sim-time sim)) 
        (lambda () (wire-set! out (not (and (wire-value in1) (wire-value in2))))))))))

(define (gate-or out in1 in2)
  (let ([sim (wire-sim out)])
    (sim-add-action! 
      sim 
      (add1 (sim-time sim)) 
      (lambda () ((wire-set! out (or (wire-value in1) (wire-value in2))))))))

(define (gate-nor out in1 in2)
  (let ([sim (wire-sim out)])
    (sim-add-action! 
      sim 
      (add1 (sim-time sim)) 
      (lambda () ((wire-set! out (not (or (wire-value in1) (wire-value in2)))))))))

(define (gate-xor out in1 in2)
  (let ([sim (wire-sim out)])
    (sim-add-action! 
      sim 
      (+ 2 (sim-time sim)) 
      (lambda () ((wire-set! out (not (eq? (wire-value in1) (wire-value in2)))))))))

;; wire gate -----------------------------------

(define (wire-not in)
  (let ([out (make-wire (wire-sim in))])
    (gate-not out in)
    out))

(define (wire-and in1 in2)
  (let ([out (make-wire (wire-sim in1))])
    (gate-and out in1 in2)
    out))

(define (wire-nand in1 in2)
  (let ([out (make-wire (wire-sim in1))])
    (gate-nand out in1 in2)
    out))

(define (wire-or in1 in2)
  (let ([out (make-wire (wire-sim in1))])
    (gate-or out in1 in2)
    out))

(define (wire-nor in1 in2)
  (let ([out (make-wire (wire-sim in1))])
    (gate-nor out in1 in2)
    out))

(define (wire-xor in1 in2)
  (let ([out (make-wire (wire-sim in1))])
    (gate-xor out in1 in2)
    out))

(define sym (make-sim))

(sim-add-action! sym 3 (lambda () (print "a")))

(define (make-counter n clk en)
  (if (= n 0)
      '()
      (let [(out (make-wire sym))]
        (flip-flop out clk (wire-xor en out))
        (cons out (make-counter (- n 1) clk (wire-and en out))))))

(define clk (make-wire sym))
(define en  (make-wire sym))
(define counter (make-counter 4 clk en))

(wire-set! en #t)

; Kolejne wywołania funkcji tick zwracają wartość licznika
; w kolejnych cyklach zegara. Licznik nie jest resetowany,
; więc początkowa wartość licznika jest trudna do określenia
(define (tick)
  (wire-set! clk #t)
  (sim-wait! sym 20)
  (wire-set! clk #f)
  (sim-wait! sym 20)
  (bus-value counter))