


```C
/* Setjmp & longjmp implementation without sigprocmask */
typedef struct {
  long rbx;
  long rbp;
  long r12;
  long r13;
  long r14;
  long r15;
  void *rsp;
  void *rip;
} Jmpbuf[1];

int Setjmp(Jmpbuf env);
noreturn void Longjmp(Jmpbuf env, int val);


_JB_RBX = 0
_JB_RBP = 1
_JB_R12 = 2
_JB_R13 = 3
_JB_R14 = 4
_JB_R15 = 5
_JB_RSP = 6
_JB_RIP = 7

        .text

        .globl Setjmp
        .type Setjmp,@function
Setjmp:
	movq    (%rsp),%r11 // return address do r11
	movq    %rbx,(_JB_RBX * 8)(%rdi) // zapisanie wartości rejestru do struktury
	movq    %rbp,(_JB_RBP * 8)(%rdi)
	movq    %r12,(_JB_R12 * 8)(%rdi)
	movq    %r13,(_JB_R13 * 8)(%rdi)
	movq    %r14,(_JB_R14 * 8)(%rdi)
	movq    %r15,(_JB_R15 * 8)(%rdi)
	movq    %rsp,(_JB_RSP * 8)(%rdi)
	movq    %r11,(_JB_RIP * 8)(%rdi) // zapisanie return address do struktury
	xorl	%eax,%eax
	ret
        .size Setjmp, . - Setjmp
        
        .globl Longjmp
        .type Longjmp,@function
Longjmp:
	movq    (_JB_RBX * 8)(%rdi),%rbx // wczytanie wartości rejestru z struktury
	movq    (_JB_RBP * 8)(%rdi),%rbp
	movq    (_JB_R12 * 8)(%rdi),%r12
	movq    (_JB_R13 * 8)(%rdi),%r13
	movq    (_JB_R14 * 8)(%rdi),%r14
	movq    (_JB_R15 * 8)(%rdi),%r15
	movq    (_JB_RSP * 8)(%rdi),%rsp
	movq    (_JB_RIP * 8)(%rdi),%r11
	movl	%esi,%eax
	testl	%eax,%eax
	jnz	1f // jeśli val != 0 to skocz do 1
	incl	%eax // dodaj jeden
1:	movq	%r11,(%rsp) // zapisanie return address na stosie
	ret
        .size Longjmp, . - Longjmp
```

Long jump zapamiętuje tylko te rejestry które są calle saved, czyli te które są zapisywane przez funkcję która wywołuje inną funkcję.
