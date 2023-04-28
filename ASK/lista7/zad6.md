```C
typedef struct A {
  long u[2];
  long *v;
} SA;

typedef struct B {
  long p[2];
  long q;
} SB;
```
```ASM
eval:
  movq    %rdi, %rax
  movq    16(%rsp), %rcx
  movq    24(%rsp), %rdx
  movq    (%rdx), %rsi
  movq    %rcx, %rdx
  imulq   %rsi, %rdx
  movq    %rdx, (%rdi)
  movq    8(%rsp), %rdx
  movq    %rdx, %rdi
  subq    %rsi, %rdi
  movq    %rdi, 8(%rax)
  subq    %rcx, %rdx
  movq    %rdx, 16(%rax)
  ret

wrap:
  subq    $72, %rsp
  movq    %rdx, (%rsp)
  movq    %rsp, %rdx
  leaq    8(%rsp), %rax
  pushq   %rdx
  pushq   %rsi
  pushq   %rdi
  movq    %rax, %rdi
  call    eval
  movq    40(%rsp), %rax
  addq    32(%rsp), %rax
  imulq   48(%rsp), %rax
  addq    $96, %rsp
  ret
```

```C
SB eval(SA s) {
    SB b;
    
    long v = *s.v;
    
    b.p[0] = s.u[1] * v;
    b.p[1] = s.u[0] - v;
    b.q = u[0] - u[1];
    
    return b;
}

long wrap(long x, long y, long z) {
    SA s;
    s.u[0] = x;
    s.u[1] = y;
    s.v = &z;
    
    SB b = eval(s);
    
    return (b.p[0] + b.p[1]) * b.q;
    }
```