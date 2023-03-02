#lang racket

(require 2htdp/image)
(require 2htdp/universe)

(define rocket ".") 

(define (picture-of-rocket h)
  (place-image rocket 50 h
               (empty-scene 100 60)))

(define scene-width 100)
(define scene-height 60)
(define rocket-x (/ scene-width 2))
(define rocket-v 1)

(define scene (empty-scene scene-width scene-height))

(define (picture-of-rocket.v2 h)
  (place-image rocket rocket-x h scene))

(define (picture-of-rocket.v3 t)
  (define distance (* rocket-v t))
  (place-image rocket rocket-x distance scene))

(define rocket-center-to-top
  (- scene-height (/ (image-height rocket) 2)))

(define (picture-of-rocket.v4 t)
  (define distance (* rocket-v t))
  (if (< distance rocket-center-to-top)
      (place-image rocket rocket-x distance scene)
      (place-image rocket rocket-x rocket-center-to-top scene)))

(define (scene-with-rocket rocket-y)
  (place-image rocket rocket-x rocket-y scene))

(define (picture-of-rocket.v5 t)
  (define distance (* rocket-v t))
  (if (< distance rocket-center-to-top)
      (scene-with-rocket distance)
      (scene-with-rocket rocket-center-to-top)))
