```ASM
puzzle2:
  movq %rdx, %r11
  xorl %r10d, %r10d
  xorl %eax, %eax
  movabsq $LONG_MIN, %r8
  movabsq $LONG_MAX, %r9
.L2: 
  cmpq %r11, %r10
  jge .L5
  movq (%rsi,%r10,8), %rcx
  cmpq %rcx, %r9
  cmovg %rcx, %r9
  cmpq %rcx, %r8
  cmovl %rcx, %r8
  addq %rcx, %rax
  incq %r10
  jmp .L2
.L5: 
  cqto
  movq %r9, (%rdi)
  idivq %r11
  movq %r8, 8(%rdi)
  movq %rax, 16(%rdi)
  movq %rdi, %rax
  ret
```

```C
#include <limits.h>

struct T {
    long max;
    long min;
    long avg;
};

struct T puzzle2(long *a, long n) {
    struct T result = { LONG_MIN, 0, LONG_MAX };
    long sum = 0;
    for (long i = 0; i < n; i++) {
        long val = a[i];
        if (val > result.max) {
            result.max = val;
        }
        if (val < result.min) {
            result.min = val;
        }
        sum += val;
    }
    result.sum_div_n = sum / n;
    return result;
}
```

struct T* puzzle8(struct T* ret, long* a, long n)

cqto Convert quadword in %rax to octoword in %rdx:%rax 

idivq S:
 - Signed divide %rdx:%rax by S
 - Quotient stored in %rax
 - Remainder stored in %rdx

(c) If the size of the aggregate exceeds two eightbytes and the first eightbyte isn’t SSE or any other eightbyte isn’t SSEUP, the whole argument
is passed in memory.