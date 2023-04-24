```C
typedef struct {
    int first;
    a_struct a[CNT];
    int last;
} b_struct;

void test (long i, b_struct *bp) {
    int n = bp->first + bp->last;
    a_struct *ap = &bp->a[i];
    ap->x[ap->idx] = n;
}

typedef struct {
    long idx;
    long x[4];
} a_struct;
```
```ASM
test:
    movl   0x120(%rsi),   %ecx              # %ecx = *(%rsi+0x120) // n = bp->last
    addl   (%rsi),        %ecx              # %ecx = %ecx + *%rsi  // n += bp->first
    leaq   (%rdi,%rdi,4), %rax              # %rax = 5 * i
    leaq   (%rsi,%rax,8), %rax              # %rax = %rsi + 8*5*i = %rsi + 40i
                                            # tu %rax trzyma a_struct
    movq   0x8(%rax),     %rdx              # %rdx = *(%rsi + 40i + 8)
    movslq %ecx,          %rcx              # (int)(%rcx) czyli (int)n
    movq   %rcx,          0x10(%rax,%rdx,8) # *(8 * %rdx + %rax + 16) = n
    retq
```

4 + pad + CNT*sizeof(a_struct) = 288

CNT*sizeof(a_struct) = 280
sizeof(a_struct) = 40
CNT = 280 /40 = 7