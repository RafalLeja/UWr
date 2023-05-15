#lang plait

(module+ test
  (print-only-errors #f))

(define-syntax my-and 
  (syntax-rules ()
    ((_ exp) exp)
    ((_ exp1 exp2 ...)
      (if exp1
        (my-and exp2 ...)
        exp1))))

(define-syntax my-or 
  (syntax-rules ()
    ((_ exp) exp)
    ((_ exp1 exp2 ...)
      (if exp1
        exp1
        (my-or exp2 ...)))))

(module+ test
  (test (my-and #f #f #f)
        (and #f #f #f))
  (test (my-and #t #t #t)
        (and #t #t #t))
  (test (my-and #t #f #f)
        (and #t #f #f))
  (test (my-and #t #t #f)
        (and #t #t #f))

  (test (my-or #f #f #f)
        (or #f #f #f))
  (test (my-or #t #t #t)
        (or #t #t #t))
  (test (my-or #t #f #f)
        (or #t #f #f))
  (test (my-or #t #t #f)
        (or #t #t #f)))

(define-syntax my-let
  (syntax-rules ()
    ((_ ((var val) ...) body)
      ((lambda (var ...) body) val ...))))

(module+ test
  (test (my-let ((x 1)) (+ x 1))
        (let ((x 1)) (+ x 1)))
  (test (my-let ((x 1) (y 2)) (+ x y ))
        (let ((x 1) (y 2)) (+ x y ))))

(define-syntax my-let*
  (syntax-rules ()
    ((_ () body ...)
      ((lambda () body ...)))
    ((_ ((var val) rest ...) body ...)
      ((lambda (var) (my-let* (rest ...) body ...)) val))))

(module+ test
  (test (my-let* ((x 1)) (+ x 1))
        (let* ((x 1)) (+ x 1)))
  (test (my-let* ((x 1) (y (+ x 2))) (+ x y ))
        (let* ((x 1) (y (+ x 2))) (+ x y ))))