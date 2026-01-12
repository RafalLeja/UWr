# Program do szybkiego obliczania skrótów MD5 przy użyciu CUDA oraz do szybkiego obliczania kolizji

## Problem kolizji w MD5

Od dłuższego czasu wiadomo, że algorytm MD5 jest podatny na kolizje,
co oznacza, że możliwe jest znalezienie dwóch różnych wejść,
które generują ten sam skrót MD5. Szybsza metoda obliczania kolizji
została opisana tutaj [Fast Collision Attack on MD5](https://eprint.iacr.org/2013/170.pdf)

## Implementacja na CPU

W celu porównania wydajności GPU oraz CPU, będę używał implementacji z [LLVM](https://llvm.org/doxygen/MD5_8cpp_source.html)

## Implementacja na GPU

Wersja GPU będzie przyspieszała obliczenia skrótów MD5 poprzez równoległe
przetwarzanie wielu bloków danych. W związku z tym że obliczanie skrótów MD5
jest sekwencyjne dla konkretnej wiadomości, główne przyspieszenie będzie
pochodzić z równoległego obliczania skrótów dla wielu różnych wiadomości
jednocześnie np. przy szukaniu kolizji.

Najprawdopodobniej jeden wątek GPU będzie obliczał skrót MD5 dla jednej wiadomości.

## Cel projektu

Projekt ma na celu porównanie implementacji CPU oraz GPU pod względem czasu wykonywania
oraz pokazać w praktyce, czemu funkcja MD5 nie powinna być używana w zastosowaniach kryptograficznych.

Rafał Leja 340879
