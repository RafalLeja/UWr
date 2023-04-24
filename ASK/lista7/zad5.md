```C
union elem {
    struct {
        long *p;            // wskaźnik:       8 bajtów
        long y;             // long:           8 bajtów
    } e1;                   // cały struct e1: 16 bajtów
    struct {
        long x;             // long:           8 bajtów
        union elem *next;   // wskaźnik:       8 bajtów
    } e2;                   // cały struct e2: 16 bajtów
}; 
```
```ASM
proc:                     # union elem* proc2(union elem* arg)
    movq 8(%rdi), %rax    #     union elem* result = arg->e2.next;
    movq (%rax),  %rdx    #     long *tempPtr = result->e1.p;
    movq (%rdx),  %rdx    #     long temp = *(tempPtr);
    subq 8(%rax), %rdx    #     temp -= result->e1.y;
    movq %rdx,    (%rdi)  #     arg->e2.x = temp;
    ret                   #     return result;

proc:
	//    \/ dereferencja drugiego pola, czyli musimy mieć wskaźnik; zatem e2
	movq 8(%rdi),%rax  // %rax = *result = arg->e2.next
	movq (%rax),%rdx   // %rdx = result->e1.p
	movq (%rdx),%rdx   // %rdx = *(result->e1.p) 
	subq 8(%rax),%rdx  // %rdx = *(result->e1.p) - result->e1.y
	movq %rdx,(%rdi)   // arg->x = *(result->e1.p) - result->e1.y
	ret
```
Prześledźmy po kolei instrukcje i stwórzmy kod w C odpowiadający funkcji `proc`:
*    `movq 8(%rdi), %rax` - stąd uzyskujemy informacje na temat typu funkcji oraz argumentu, jako że do `%rax` wysyłamy adres, to funkcja będzie typu `union elem*`, podobnie jak jej argument, a sama instrukcja odpowiada `union elem* result = arg->e2.next`
*    `movq (%rax), %rdx` - odpowiada to instrukcji `long *tempPtr = result->e1.p`
*    `movq (%rdx), %rdx` - `long temp = *(tempPtr);`, w assemblerowym kodzie linijki 3/4 odpowiadają instrukcji z linijki 13 w C.

Po assemblerowym kodzie możemy wywnioskować z którą strukturą pracujemy tylko przez to, czy odwołujemy się do wartości, czy adresów: zauważmy, że pierwszym elementem `struct e1` jest wskaźnik, a drugim wartość, a w `struct e2` jest odwrotnie.

```C
union elem* proc(union elem* arg){
    union elem* result = arg->e2.next;
    long temp = *(result->e1.p);
    temp -= result->e1.y;
    arg->e2.x = temp;
    return result;
}
```
