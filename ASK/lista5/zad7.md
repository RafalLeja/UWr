1. 400590 <switch_prob>:
2. 400590: 48 83 ef 3c subq $0x3c,%rsi
3. 400594: 48 83 fe 05 cmpq $0x5,%rsi
4. 400598: 77 29 ja *0x4005c3
5. 40059a: ff 24 f5 f8 06 40 00 jmpq *0x4006f8(,%rsi,8)
6. 4005a1: 48 8d 04 fd 00 00 00 00 lea 0x0(,%rdi,8),%rax # return x*8
7. 4005a9: c3 retq
8. 4005aa: 48 89 f8 movq %rdi,%rax
9. 4005ad: 48 c1 f8 03 sarq $0x3,%rax #return x >> 3
10. 4005b1: c3 retq
11. 4005b2: 48 89 f8 movq %rdi,%rax // case 62:
12. 4005b5: 48 c1 e0 04 shlq $0x4,%rax // x*16
13. 4005b9: 48 29 f8 subq %rdi,%rax // -x
14. 4005bc: 48 89 c7 movq %rax,%rdi 
15. 4005bf: 48 0f af ff imulq %rdi,%rdi //case 65: x *= x
16. 4005c3: 48 8d 47 4b leaq 0x4b(%rdi),%rax // x += 75
17. 4005c7: c3 retq

Zrzut pamięci przechowującej
tablicę skoków:

18. (gdb) x/6gx 0x4006f8
19. 0x4006f8: 0x4005a1
20. 0x400700: 0x4005a1
21. 0x400708: 0x4005b2
22. 0x400710: 0x4005c3
23. 0x400718: 0x4005aa
24. 0x400720: 0x4005bf

```C
long switch_prob(long x, long n)
{
    switch(n)
    {
        case 60:
        case 61:
            return x * 8;
        case 64:
            return x >> 3;
        case 62:
            x *= 15;
        case 65:
            x *= x;
        default:   
            return x + 75;
    }
}
```