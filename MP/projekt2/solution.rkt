#lang racket
(require data/heap)
#;(provide sim? wire?
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

#;(define (flip-flop out clk data)
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

(struct sim (time heap))

(define (make-sim)
  (sim 0 (make-heap (lambda (a b) (<= (action-time a) (action-time b))))))

(define (run-heap h t)
  (cond
      [(= (heap-count heap) 0) (void)]
      [(<= ct (action-time (heap-min heap))) ()]))

(define (sim-wait! s t)
  (let 
    ([ct (+ sim-time t)]
    [heap (sim-heap)])
    (run-heap h ct)
    (sim ct (sim-heap s))))

(struct wire (sim value actions))

(define (make-wire sim)
  (wire sim 0 '()))

(define (wire-set! w v)
  (wire (wire-sim w) v (wire-actions w))
  (for-each (lambda (a) (a)) (wire-actions w)))

(define (wire-on-change! w a)
  (wire (wire-sim w) (wire-value w) (append a (wire-actions w))))