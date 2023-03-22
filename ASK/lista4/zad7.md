1. Podziel każdą liczbę na dwie części 64-bitowe:
x = x1 * 2^64 + x0
y = y1 * 2^64 + y0
2. Oblicz cztery iloczyny:
a = x1 * y1
b = x1 * y0
c = x0 * y1
d = x0 * y0
3. Dodaj iloczyny «b» i «c», aby uzyskać wynik pośredni «e»:
e = b + c
4. Przesuń wynik pośredni «e» o 64 bity w lewo, aby uzyskać wartość «f»:
f = e << 64
5. Dodaj iloczyny «a» i «f», aby uzyskać ostateczny wynik:
wynik = a + f + d

```ASM
; Argumenty:
; rdi - wskaźnik na liczbę x
; rsi - wskaźnik na liczbę y

; Rejestry pomocnicze:
; rax, rbx, rcx, rdx - rejestry ogólnego przeznaczenia
; r8, r9 - rejestry pomocnicze

multiply:
    ; Wczytanie wartości x
    mov rax, QWORD PTR [
```