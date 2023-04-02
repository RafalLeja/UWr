```ASM
subq %rsi, %rdi ; x := x - y, ustawienie flagi CF dla (x < y)
sbb %rax, %rax  ; %rax = CF ? -1 : 0
neg  %rdi       ; x := -x, neg zapala CF dla liczb różnych od 0
adc  %rax, %rax ; %rax + (%rax + CF)
ret
```