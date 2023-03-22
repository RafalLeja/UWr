```ASM
.global swap_endian
swap_endian:
    mov %edi, %eax     ; Przekopiowanie argumentu do rejestru %eax
    ror $8, %eax       ; Przesunięcie o 8 bitów w prawo z cyklem (little-endian -> big-endian)
    ror $16, %eax      ; Przesunięcie o 16 bitów w prawo z cyklem (little-endian -> big-endian)
    ror $8, %eax       ; Przesunięcie o 8 bitów w prawo z cyklem (little-endian -> big-endian)
    mov %eax, %eax     ; Przekopiowanie wyniku do rejestru %eax (zwracanie wyniku)
    ret                ; Powrót z procedury
```

```C
uint32_t x = ...;
x = (x >> 8) | (x << 24);
```

lub 

```C
uint32_t x = ...;
x = (x << 24) | (x >> 8);
```