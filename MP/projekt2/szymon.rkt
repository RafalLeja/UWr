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

          [flip-flop (-> wire? wire? wire? void?)]
          )
         )

;ZARZĄDZANIE CZASEM
(struct event (
               time
               action
               ) #:transparent) ;definiujemy zdarzenie, czas akcja priorytet zdarzenia

(define (compare-events event1 event2) ;porównywator zdarzeń
  (<= (event-time event1) (event-time event2))
  )

;uruchomienie symulacji sim, przez delta-t jednostek czasu
(define (sim-wait! sim delta-t)
  (let ([left-time (+ (sim-time sim) delta-t)] ;pozostały czas, jaki mamy do wykorzystania
        [evts (sim-event-queue sim)];zdarzenia
        )
    (cond
      ;jak sterta jest pusta, to przypisuję po prostu nowy czas
      [(= (heap-count evts) 0)
       (set-sim-current-time! sim left-time)
       ]
      ;jeżeli jest czas na wywołanie akcji i przesunięci
      [(> left-time (event-time (heap-min evts)))
       (let ([min (heap-min evts)])
         (heap-remove-min! evts) ;usuwamy aktualne zdarzenie ze sterty
         (set-sim-current-time! sim (event-time min))
         (print (heap-count evts)) ;właściwe przesunięcie czasu symulacji o czas z danej akcji, ustalamy od razu czas, bo kolejne akcje  mogą być wywołane z aktualnej
         ((event-action min)) ;wywołanie akcji z danego wydarzenia
         (sim-wait! sim (- left-time (event-time min))) ;od czasu o jaki możemy się jeszcze przesunąć odejmujemy czas wykonania naszej akcji  
         )
       
       ]
      ;jeżeli wywołanie następnej akcji nie będzie możliwe, przez brak czasu, delta-t nie będzie wystarczająco duża
      [(<= left-time (event-time (heap-min evts)))
       (set-sim-current-time! sim left-time)
       ]

      )
    )
  )



;SYMULACJA

;jak wygląda nasza symulacja
(struct sim (
  [current-time #:mutable]
  event-queue
  ) #:transparent
)


;utworzenie symulacji
(define (make-sim)
  (sim 0
       ; robię stertę event'ów
       (make-heap (lambda (ev1 ev2) (<= (event-time ev1) (event-time ev2) )))
       )
  )



;dowiedzenie się o czasie symulacji
(define (sim-time sim)
  (sim-current-time sim)
  )

;dodawanie akcji do symulacji, czyli utworzenie event'u
(define (sim-add-action! sim time action)
      (heap-add! (sim-event-queue sim) (event (+ (sim-time sim) time) action)) ;dodanie do sterty nowego even'tu
      )

;PRZEWODY

;utworzenie przewodu
(struct wire 
   (sim ; symulacja, do której przewód należy
    [val #:mutable] ;wartość w przewodzie #f albo #t
    [on-change-procedures  #:mutable] ;kolekcja procedur do wywołania, gdy sygnał zmienie wartość
    ) #:transparent 
)

;utworzenie przewodu z daną symulacją
;przewód należy do jednej symulacji, bo my 'puszczamy' naszą sumulację właśnie po przeowdzie byłby 'konflikt' sygnałów
(define (make-wire simulation)
  (wire
   simulation
   #f
   '()
   )
  )

;dodawanie akcji, które wykonają się za każdym razem, gdy zmieni się wartość przewodu
(define (add-on-change-action wire action)
  (set-wire-on-change-procedures! wire (cons action (wire-on-change-procedures wire)))
  )


;dziwny stan początkowy to stan, w którym w przewodzie jest jakaś akcja, która nie została wykonana, a my dodajemy nową
;podłączamy do kabla akcję, która wykona się w razie zmiany jego stanu
;poniższa funkcja to wyzwalacz akcji, w razie zmiany
(define (wire-on-change! wire action)
  (begin
    ;dodanie akcji do przewodu
    (add-on-change-action wire action)
    ;wywołanie dodanej akcji
    (action)
    )
  )


;podejrzenie wartości przewodu
(define (wire-value wire)
  (wire-val wire)
  )

;wywołanie wszystkich akcji, podpiętych do kabla
(define (call-each-action actions)
  (if (null? actions)
      void
      (begin
        ((first actions))
        (call-each-action (rest actions))
        )
      )
  )

(define (wire-set! wire new-value)
  ;jeżeli ustawiona w przewodzie wartość jest inna niż obecna tam wartość
  (if (not (eq? (wire-value wire) new-value))
      ;zmieniamy wartość w przewodzie i wywołujemy podpięte akcje
      (begin
        (set-wire-val! wire new-value)
        (call-each-action (wire-on-change-procedures wire))
        (void)
        )
      (void)
      )
  )



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


;BRAMKI LOGICZNE
;NOT
(define (gate-not wire-out wire-in)
  ;dodajemy tą akcję, do akcji, które będą uruchamiane w przypadku zmiany stanu przewodu
  (wire-on-change! wire-in
                   (lambda ()
                     (sim-add-action!
                      (wire-sim wire-out) ;symulacja, która nas interesuje to ta, która się teraz odbywa na wyjściowym kablu
                      1 ;czas trwania wyjściowej symulacji, automatycznie się zwiększa o 1, taki jest koszt NOT'a
                      (lambda () (wire-set! wire-out (not (wire-value wire-in)))) ;ustawiamy nową wartość wyjściowego kabla, funkcja anonimowa, wywołana w razie zmiany stanu kabla
                      )
                     )
                   )
  )


;AND
(define (gate-and wire-out wire-in1 wire-in2)
  ;skonstruujemy akcję, którą będziemy podawać
  (define update-output
    ;update-output podawany jest jako funkcja
    (lambda ()
      (sim-add-action! ;dodajemy akcję do symulacji
       (wire-sim wire-out)
       1 ;dodajemy czas trwania, ANDa do czasu symulacji
       (lambda () (wire-set! wire-out (and (wire-value wire-in1) (wire-value wire-in2)))) ;sim-add-action przyjmuje akcję, stąd funkcja anonimowa
      ))
    )
    (wire-on-change! wire-in1 update-output) ;jeżeli zmienie się sygnał w przewodzie 1, to wykonamy akcję która ANDuje obie wartości na kablach
    (wire-on-change! wire-in2 update-output)
  )



;NAND
(define (gate-nand wire-out wire-in1 wire-in2)
  (define update-output
    (lambda ()
      (sim-add-action!
       (wire-sim wire-out)
       1
       (lambda () (wire-set! wire-out (nand (wire-value wire-in1) (wire-value wire-in2)))) 
      ))
    )
    (wire-on-change! wire-in1 update-output) 
    (wire-on-change! wire-in2 update-output)
  )



;OR
(define (gate-or wire-out wire-in1 wire-in2)

  (define update-output
    (lambda ()
      (sim-add-action! 
       (wire-sim wire-out)
       1
       (lambda () (wire-set! wire-out (or (wire-value wire-in1) (wire-value wire-in2))))
       )))
    (wire-on-change! wire-in1 update-output)
    (wire-on-change! wire-in2 update-output)
  )



;NOR
(define (gate-nor wire-out wire-in1 wire-in2)
  (define update-output
    (lambda ()
      (sim-add-action! 
       (wire-sim wire-out)
       1
       (lambda () (wire-set! wire-out (nor (wire-value wire-in1) (wire-value wire-in2)))) 
      ))
    )
    (wire-on-change! wire-in1 update-output) 
    (wire-on-change! wire-in2 update-output)
  )



;XOR
(define (gate-xor wire-out wire-in1 wire-in2)
  (define update-output
    (lambda ()
      (sim-add-action!
       (wire-sim wire-out)
       2
       (lambda () (wire-set! wire-out (xor (wire-value wire-in1) (wire-value wire-in2))))
      ))
    )
    (wire-on-change! wire-in1 update-output)
    (wire-on-change! wire-in2 update-output)
  )






;PRZEWODY Z BRAMKAMI
;zwracamy przewód, złączony z bramką, która nim steruje

;NOT
(define (wire-not wire-in)
  (let* ([out-sim (wire-sim wire-in)]
         [wire-out (make-wire out-sim)]) ;tworzymy przewód w nowej symulacji, dla naszego wyjścia
    (wire-on-change! wire-in
                     (lambda ()
                       (sim-add-action!
                        (wire-sim wire-out)
                        1
                        (lambda () (wire-set! wire-out (not (wire-value wire-in))))
                        )
                       )
                     )
    wire-out
    )
  )

;AND
(define (wire-and wire-in1 wire-in2)
  (let* ([out-sim (wire-sim wire-in1)] ;tworzymy symulację do nowego przewodu
         [wire-out (make-wire out-sim)]) ;tworzymy nowy przewód
    (begin
        (define update-output
          (lambda ()
          (sim-add-action! 
           (wire-sim wire-out)
           1
           (lambda () (wire-set! wire-out (and (wire-value wire-in1) (wire-value wire-in2)))) 
           ))
          )
        (wire-on-change! wire-in1 update-output)
        (wire-on-change! wire-in2 update-output)
      )
    wire-out
    )
  )




;NAND
(define (wire-nand wire-in1 wire-in2)
  (let* ([out-sim (wire-sim wire-in1)]
         [wire-out (make-wire out-sim)])
    (begin
        (define update-output
          (lambda ()
          (sim-add-action! 
           (wire-sim wire-out)
           1
           (lambda () (wire-set! wire-out (nand (wire-value wire-in1) (wire-value wire-in2))))
           ))
          )
        (wire-on-change! wire-in1 update-output)
        (wire-on-change! wire-in2 update-output)
      )
    wire-out
    )
  )



;OR
(define (wire-or wire-in1 wire-in2)
  (let* ([out-sim (wire-sim wire-in1)]
         [wire-out (make-wire out-sim)])
    (begin
        (define update-output
          (lambda ()
          (sim-add-action! 
           (wire-sim wire-out)
           1
           (lambda () (wire-set! wire-out (or (wire-value wire-in1) (wire-value wire-in2))))
           ))
          )
        (wire-on-change! wire-in1 update-output)
        (wire-on-change! wire-in2 update-output)
      )
    wire-out
    )
  )




;NOR
(define (wire-nor wire-in1 wire-in2)
  (let* ([out-sim (wire-sim wire-in1)]
         [wire-out (make-wire out-sim)])
    (begin
        (define update-output
          (lambda ()
          (sim-add-action! 
           (wire-sim wire-out)
           1
           (lambda () (wire-set! wire-out (nor (wire-value wire-in1) (wire-value wire-in2))))
           ))
          )
        (wire-on-change! wire-in1 update-output)
        (wire-on-change! wire-in2 update-output)
      )
    wire-out
    )
  )



;XOR
(define (wire-xor wire-in1 wire-in2)
  (let* ([out-sim (wire-sim wire-in1)]
         [wire-out (make-wire out-sim)])
    (begin
        (define update-output
          (lambda ()
          (sim-add-action! 
           (wire-sim wire-out)
           2
           (lambda () (wire-set! wire-out (xor (wire-value wire-in1) (wire-value wire-in2))))
           ))
          )
        (wire-on-change! wire-in1 update-output)
        (wire-on-change! wire-in2 update-output)
      )
    wire-out
    )
  )




(define (flip-flop out clk data)
  (define sim (wire-sim data))
  (define w1  (make-wire sim))
  (define w2  (make-wire sim))
  (define w3  (wire-nand (wire-and w1 clk) w2))
  (gate-nand w1 clk (wire-nand w2 w1))
  (gate-nand w2 w3 data)
  (gate-nand out w1 (wire-nand out w3)))


;testy dla flip-flop
#;(define (test-flip-flop-1)
  (let* ([s (make-sim)]
        [data (make-wire s)]
        [clk (make-wire s)]
        [out (make-wire s)])
    (wire-set! clk #t) ; Set CLK to high (1)
    (wire-set! data #t) ; Set DATA to high (1)
    (flip-flop out clk data)
    (sim-wait! s 10) ; Advance the simulation by 10 time units
    (display (format "Output after 10 time units with CLK high and DATA high: ~a\n" (wire-value out)))))

;(test-flip-flop-1)


;(define sim3 (make-sim))
;(define not-input (make-wire sim3))
;(define not-output (make-wire sim3))
;(gate-not not-output not-input)

;(wire-set! not-input #t)
;(sim-wait! sim3 1) ; Czekamy trochę czasu, aby zmiana zdążyła się zadziałać
;(printf "Wartość not-output (powinno być #f): ~a~%" (wire-value not-output))


;(define sim5 (make-sim))
;(define a-input-2 (make-wire sim5))
;(define b-input-2 (make-wire sim5))
;(define and-output-wire-2 (make-wire sim5))



;(display "Test 1 AND (true, true) -> true. Wyjście bramki AND: ")
;(wire-set! a-input-2 #t)
;(sim-wait! sim5 1) ; Czekamy na propagację sygnału
;(wire-set! b-input-2 #t)
;(sim-wait! sim5 1) ; Czekamy na propagację sygnału oraz na przetworzenie przez bramkę AND

;(gate-and and-output-wire-2 a-input-2 b-input-2)
;(sim-wait! sim5 1)

;(display (wire-value and-output-wire-2)) ; Powinno być true (#t)


(trace wire-set! call-each-action wire-on-change! sim-wait! event-action)
