```ASM
pointless:
  pushq %r14
  pushq %rbx
  pushq %rax
  movq %rsi, %r14
  movq %rdi, %rbx
  testq %rdi, %rdi
  jle .L1
  leaq (%rbx,%rbx), %rdi
  movq %rsp, %rsi
  callq pointless
  addq (%rsp), %rax
  jmp .L3
.L1: xorl %eax, %eax
.L3: addq %rax, %rbx
  movq %rbx, (%r14)
  addq $8, %rsp
  popq %rbx
  popq %r14
  retq
```

```C
long pointless(long n, long *p) {
    if (n <= 0) {
        return 0;
    } else {
        long temp = pointless(n - 1, p);
        *p += 2 * temp;
        return temp;
    }
}
```

Rekord aktywacji (stack frame) zawiera następujące elementy:

 - Rejestry zapisane przez funkcję wołaną (callee-saved registers): %r14, %rbx
 - Zmienne lokalne: brak
 - Adres powrotu: wartość z wierzchołka stosu (%rsp) po instrukcji "addq $8, %rsp"

Wiersz 11 (po wywołaniu rekurencyjnym) modyfikuje wartość rejestru %rsp, aby utworzyć nowy stos dla rekurencji. Zgodnie z [1, 3.2.2], "w momencie wejścia do funkcji %rsp musi być wielokrotnością 16". W tym przypadku wartość %rsp jest przesuwana o 8 bajtów po wykonaniu instrukcji "addq $8, %rsp". Zatem wartość %rsp w wierszu 11 jest podzielna przez 16.

Autorzy ABI zdecydowali się na taką konwencję, aby umożliwić efektywne zarządzanie stosami przez sprzętowe jednostki przetwarzające. Wyrównanie wartości %rsp do granicy 16 bajtów pozwala uniknąć konieczności przesuwania danych między rejestrami a pamięcią w przypadku operacji na stosie, co przyspiesza wykonywanie kodu.