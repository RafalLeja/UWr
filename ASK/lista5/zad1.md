```ASM
addu:
    movq %rdi, %rax       # result = x
    addq %rsi, %rax       # result += y
    cmpq %rsi, %rax       # compare result with y
    jae overflow          # jump if result is greater or equal to y
    cmpq %rdi, %rax       # compare result with x
    jae done              # jump if result is greater or equal to x
    jmp overflow          # otherwise, jump to overflow
done:
    ret
overflow:
    movq $-1, %rax        # return ULONG_MAX
    ret
```

Rozwiązanie przy użyciu instrukcji `sbb`:

```ASM
addu:
    movq %rdi, %rax        # result = x
    addq %rsi, %rax        # result += y
    cmpq %rsi, %rax        # compare result with y
    sbbq %rax, %rax        # set result to -1 if result < y, otherwise 0
    cmovnb %rdi, %rax      # set result to x if result < y, otherwise keep result
    ret
```

W tym rozwiązaniu, `addu` przyjmuje dwa argumenty, `uint64_t x` i `uint64_t y`, w rejestrach `%rdi` i `%rsi` odpowiednio i zwraca wynik w rejestrze `%rax`.

Instrukcje `movq` i `addq` działają jak w poprzednim rozwiązaniu.

Potem, korzystając z instrukcji `cmpq` i `sbbq`, sprawdzamy, czy wynik `x + y` jest większy lub równy `y`. Jeśli tak, instrukcja `sbbq %rax, %rax` ustawia wartość `%rax` na `-1`, co oznacza, że wynik powinien być ustawiony na `ULONG_MAX`. W przeciwnym razie, `%rax` zostanie ustawione na `0`.

Ostatnim krokiem jest instrukcja warunkowa `cmovnb %rdi, %rax`. Jeśli `%rax` jest ujemne, co oznacza, że `x + y` było większe lub równe `ULONG_MAX`, instrukcja ta ustawia `%rax` na wartość `x`. W przeciwnym razie, `%rax` pozostaje niezmieniony, co jest równoważne z ustawieniem go na `x + y`.

Wynik jest teraz zwracany w rejestrze `%rax` zgodnie z konwencją wywołania funkcji w asemblerze x86-64.