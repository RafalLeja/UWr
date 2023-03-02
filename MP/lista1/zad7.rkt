#lang racket

(require 2htdp/image)
(require 2htdp/universe)

(define rocket .)

(define scene-width 100)
(define scene-height 60)
(define rocket-x (/ scene-width 2))
(define start-time 3)
(define rocket-power 0.01)

(define scene (empty-scene scene-width scene-height))

(define rocket-center-to-top
  (- scene-height (/ (image-height rocket) 2)))

(define (scene-with-rocket t)
  (define y (* rocket-power (/ (* t t) 2)))
  (place-image rocket rocket-x (- scene-height y (/ (image-height rocket) 2)) scene))


(define (tick x) (if (<= x 0) 0 x))

(define (timer t) (tick (- start-time (quotient t 30))))

(define (scene-countdown t) 
    (place-image (text (number->string t) (/ scene-height 5) "black") (/ scene-width 2) (/ scene-height 2) scene))

(define (launch t) 
    (define czas (timer t))
    (if (= czas 0) (scene-with-rocket (- t (* 30 start-time))) (scene-countdown czas)))

(animate launch)