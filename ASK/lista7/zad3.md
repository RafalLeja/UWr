```C
long A[R][S][T];

long store_elem(long i, long j, long k, long *dest){
    *dest = A[i][j][k];
    return sizeof(A);
}
```
```ASM
store_elem:
    leaq (%rsi,%rsi,2), %rax    # %rax = 3j
    leaq (%rsi,%rax,4), %rax    # %rax = j + 12j = 13j
    movq %rdi,          %rsi    # %rsi = i
    salq $6,            %rsi    # %rsi = 2^6*i = 64i
    addq %rsi,          %rdi    # %rdi = 65i
    addq %rax,          %rdi    # %rdi = 65i + 13j
    addq %rdi,          %rdx    # %rdx = 65i + 13j + k
    movq A(,%rdx,8),    %rax    # %rax = A + 8 * (65i + 13j + k)
    movq %rax,          (%rcx)  # %rax = *dest
    movq $3640,         %rax    # %rax = sizeof(A)
    ret
```

sizeof(A) = 3640B = 455 long

$(65i + 13j + k) = (i*S*T + j*T + k)$

$T=13$

$S =5$

$R=\frac{455}{5*13} =7$