### Definicje symboli:
Linia 3 - .type

### Czemu assembler nie może wygenerować ostatecznego ciągu bajtów?

Ponieważ pliki *.c nie zostały jeszcze skonsolidowane i nie znają offsetu który powstanie między funkcjami po ich połączeniu, tworzona jest zmienna, w której miejsce zostanie wpisany offset

```ASM
start.s:
    call	is_even@PLT ;procedure linkage table

   6:   e8 00 00 00 00          call   b <_start+0xb>
```