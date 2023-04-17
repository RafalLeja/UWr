Konwencja wołania procedur:
 * przy wywołaniu procedury %rsp musi być podzielny przez 16
 * (caller saved) – jeśli procedura wywołująca (caller) korzysta z rejestrów %rax, %rdi, %rsi, %rdx, %rcx, %r8, …, %r11, to musi zapamiętywać stan tych rejestrów przed wywołanienm innej procedury, która z nich korzysta, ponieważ procedura wołana (callee) może zmodyfikować zawartość tych rejestrów bez ich zapisu.
 * (callee saved) – jeśli procedura wołana (callee) chce skorzystać z rejestru %rbx, %r12, %r13, %r14, %rbp, to musi zapamiętać ich wartości przed użyciem, a następnie przywrócić ich wartość przed zakończeniem swojego działania.
 * Procedura przed zakończeniem musi oczywiścić stos z wartości, które na niego wstawiła.

```ASM
M:   pushq %rdi            // zapisujemy n na stosie
     testq %rdi, %rdi       
     je    .L2             // jeśli n==0 (ZF==1) skocz do return n
     leaq  -1(%rdi), %rdi  // przekazujemy n-1 jako argument
     call  M               // wywołanie t1 = M(n-1)
     movq  %rax, %rdi      // przekazujemy wynik jako parametr
     call  F               // wywołanie t2 = F(t1) = F(M(n-1))
     movq  (%rsp), %rdi    // wyciągamy n ze stosu
     subq  %rax, %rdi      // n = n - t2
.L2: movq  %rdi, %rax      // zwracamy n
     ret
```

```ASM  ;poprawka
M:   pushq %rdi            
     testq %rdi, %rdi      
     je    .L2              
     leaq  -1(%rdi), %rdi  
     call  M               
     movq  %rax, %rdi      
     call  F               
     movq  (%rsp), %rdi    
     subq  %rax, %rdi       
.L2: movq  %rdi, %rax
     popq  %rdi             //zdjęcie ze stosu
     ret
```

```ASM
F:   testq %rdi, %rdi      
     je    .L3             // jeśli n == 0 return 1
     movq  %rdi, %r12      // zapisujemy wartość n w r12
     leaq  -1(%rdi), %rdi  // przekazujemy n-1 jako argument
     call  F               // wywołanie t1 = F(n-1)
     movq  %rax, %rdi      // t2 = F(n-1) przekazujemy jako argument
     call M                // wywołanie M(t2)
     subq  %rax, %r12      // n = n - temp2
     movq  %r12, %rax      // zwracamy n
     ret
L3:  movl  $1, %eax        // zwracamy 1
     ret
```
```ASM  ;poprawka
F:   testq %rdi, %rdi      
     je    .L3             
     pushq %r12            // przechowanie %r12 na stosie
     movq  %rdi, %r12      
     leaq  -1(%rdi), %rdi  
     call  F               
     movq  %rax, %rdi      
     call M                
     subq  %rax, %r12      
     movq  %r12, %rax
     popq  %r12
     ret
L3:  movl  $1, %eax
     ret
```


```C
long M (long x) {
    if (x) {
        long temp = x - 1;
        temp = M(temp);
        temp = x;
        x -= F(temp);
    }
    return x
}

long F (long y) {
    if (y == 0) return 1
    else {
        long temp = y - 1;
        temp = F(temp);
        y -= M(temp);
        return y
    }
}
```