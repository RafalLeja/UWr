```C
typedef struct {
    int x[A][B];
    long y;
} str1;

typedef struct {
    char array[B];    B <= 8B 
    int t;            = 4B
    short s[A];       16 >= 2*A <= 20
    long u;
} str2;

void set_val(str1 *p, str2 *q) {
    long v1 = q->t;
    long v2 = q->u;
    p->y = v1 + v2;
}
```
```asm
set_val:
    movslq 8(%rsi),  %rax         ; 4 < B <= 8
    addq   32(%rsi), %rax         ; 8 <= A <= 10
    movq   %rax,     184(%rdi)    ; 177 < 4*A*B <= 184
    ret
```
44.25 < A*B <= 46

| x | A=8 | A=9 | A=10 |
|---|-----|-----|------|
|B=5| 40  |   45|    50|
|B=6|   48|   54|    60|


A = 9
B = 5