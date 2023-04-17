```ASM
puzzle6:
    subq    $24, %rsp      // zmniejszamy wskaźnik na stos o 24 bajty (alokujemy miejsce na stosie)
    movq    %rsp, %rdi     
    call    readlong       // wywołujemy readlong, przekazujemy mu wskaźnik na stos
    leaq    8(%rsp), %rdi
    call    readlong       // wywołujemy readlong, przekazujemy mu wskaźnik na kolejny element na stosie
    movq    (%rsp), %rax   // przenosimy do raxa wynik pierwszego wywołania readlonga
    cqto
    idivq   8(%rsp)        // dzielimy wynik pierwszego wywolania readlonga przez wynik drugiego (część całkowitą otrzymujemy w raxie, a resztę z dzielenia w rdx)
    xorl    %eax, %eax     
    testq   %rdx, %rdx     // ustawiamy ZF na 1, gdy nie otrzymaliśmy reszty, 0 wpp
    sete    %al            // zapisujemy najmniej znaczący bit wartością flagi ZF  
    addq    $24, %rsp      // zwiększamy wskaźnik na stos o 24 bajty (zwalniamy miejsce na stosie)
    ret
```

|Rekordy aktywacji funkcji        |rozmiar|
|---------------------------------|-------|
|return address                   |8      |
|puste                            |8      |
|long (readlong z param. 8(%rsp)) |8      |
|long (readlong z param. %rsp)    |8      |

```c
void readlong(long *x);

long puzzle6(void){
    long x, y;
    readlong(&x);
    readlong(&y);
    return x % y == 0;
}
```