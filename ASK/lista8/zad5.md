```C
char *somestr(void) {
  return "Hello, world!";
}
```
```ASM
somestr:    
    mov     $0x472004, %eax
    ret
    ...

    movb    $0x0, $0x5(%rax) ;-> Segmentation Fault
    call    0x404290 <puts>
```

stała "Hello, world!" została umieszczona pod rejestrem %rax

```C
char *somestr(void) {
  static char word[14] = "Hello, world!";
  return word;
}
```
```ASM
somestr:
    mov     $0x4bc0f0, %eax
    ret
    ...
    movb    $0x0, 0x5(%rax)
    call    0x40ac90 <_IO_puts>  
```

teraz zmienna jest na stosie
