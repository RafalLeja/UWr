```ASM
puzzle2:
  movq %rdx, %r11
  xorl %r10d, %r10d
  xorl %eax, %eax
  movabsq $LONG_MIN, %r8
  movabsq $LONG_MAX, %r9
.L2: cmpq %r11, %r10
  jge .L5
  movq (%rsi,%r10,8), %rcx
  cmpq %rcx, %r9
  cmovg %rcx, %r9
  cmpq %rcx, %r8
  cmovl %rcx, %r8
  addq %rcx, %rax
  incq %r10
  jmp .L2
.L5: cqto
  movq %r9, (%rdi)
  idivq %r11
  movq %r8, 8(%rdi)
  movq %rax, 16(%rdi)
  movq %rdi, %rax
  ret
```