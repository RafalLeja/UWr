#lang racket
(require data/heap)
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

(struct action (time proc))

;; sim ------------------------------

(struct sim ([time #:mutable] [heap #:mutable]))

(define (make-sim)
  (sim 0 (make-heap (lambda (a b) (<= (action-time a) (action-time b))))))

(define (sim-wait! s t)
  (let 
    ([ct (+ (sim-time s) t)]
    [heap (sim-heap s)])
    (cond
      [(= (heap-count heap) 0) 
        (set-sim-time! s ct)]
      [(> ct (action-time (heap-min heap))) 
          (let ([curr (heap-min heap)])
            (heap-remove-min! heap)
            (set-sim-time! s (action-time curr))
            ((action-proc curr)) 
            (sim-wait! s (- ct (action-time curr))))]
      [(<= ct (action-time (heap-min heap))) 
        (set-sim-time! s ct)])))

(define (sim-add-action! s t proc)
    (heap-add! (sim-heap s) (action (+ (sim-time s) t) proc)))

;; wire -------------------------------------

(struct wire (sim [value #:mutable] [actions #:mutable]))

(define (make-wire sim)
  (wire sim #f null))

(define (wire-on-change! w a)
  (set-wire-actions! w (append (wire-actions w) (list a)))
  (a))

(define (wire-set! w v)
  (if (not (eq? v (wire-value w)))
    (begin 
      (set-wire-value! w v)
      (for-each (lambda (a) (a)) (wire-actions w)))
    (void)))

;; gate -----------------------------

(define (gate-not out in)
  (let*
   ([sim (wire-sim out)]
    [proc 
      (lambda () (sim-add-action! 
        sim 
        1
        (lambda () (wire-set! out (not (wire-value in))))))])
    (wire-on-change! in proc)))
  
(define (gate-and out in1 in2)
  (let*
   ([sim (wire-sim out)]
    [proc 
      (lambda () (sim-add-action! 
        sim 
        1 
        (lambda () (wire-set! out (and (wire-value in1) (wire-value in2))))))])
    (wire-on-change! in1 proc)
    (wire-on-change! in2 proc)))

(define (gate-nand out in1 in2)
  (let*
   ([sim (wire-sim out)]
    [proc 
      (lambda () (sim-add-action! 
        sim 
        1 
        (lambda () (wire-set! out (nand (wire-value in1) (wire-value in2))))))])
    (wire-on-change! in1 proc)
    (wire-on-change! in2 proc)))

(define (gate-or out in1 in2)
  (let* 
   ([sim (wire-sim out)]
    [proc 
      (lambda () (sim-add-action! 
        sim 
        1 
        (lambda () (wire-set! out (or (wire-value in1) (wire-value in2))))))])
    (wire-on-change! in1 proc)
    (wire-on-change! in2 proc)))

(define (gate-nor out in1 in2)
  (let* 
   ([sim (wire-sim out)]
    [proc 
      (lambda () (sim-add-action! 
        sim 
        1 
        (lambda () (wire-set! out (nor (wire-value in1) (wire-value in2))))))])
    (wire-on-change! in1 proc)
    (wire-on-change! in2 proc)))

(define (gate-xor out in1 in2)
  (let* 
   ([sim (wire-sim out)]
    [proc 
      (lambda () (sim-add-action! 
        sim 
        2 
        (lambda () (wire-set! out (xor (wire-value in1) (wire-value in2))))))])
    (wire-on-change! in1 proc)
    (wire-on-change! in2 proc)))

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

