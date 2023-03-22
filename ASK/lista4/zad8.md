```ASM
movb $0x20, %bl     # ustawia %bl na wartość początkową, czyli kod ASCII pierwszego drukowalnego znaku
movq %rax, %rcx     # kopiujemy zawartość %rax do %rcx
andq $0xffffffdf, %rcx  # wyzerowujemy piąty bit w %rcx, co zamienia małą literę na dużą
cmpb $0x7f, %bl     # porównujemy %bl z wartością końcową, czyli kodem ASCII ostatniego drukowalnego znaku
jge done            # jeśli %bl >= 0x7f, to kończymy
nextchar:           # etykieta pętli
testb %al, %al      # sprawdzamy, czy %al jest równy zeru
jz done             # jeśli tak, to kończymy
movb (%rax), %dl    # pobieramy bajt z adresu wskazywanego przez %rax i zapis
```

```ASM
mov cl, 0x20   ; ustalenie wartości dolnej granicy zakresu znaków ASCII
mov ch, 0x5f   ; ustalenie wartości górnej granicy zakresu znaków ASCII

xor rcx, rcx   ; wyzerowanie rejestru rcx

petla:
    cmp byte ptr [rax+rcx], cl   ; porównanie bajtu w %rax+rcx z dolną granicą zakresu
    jb koniec                   ; jeśli jest mniejszy, to koniec pętli
    cmp byte ptr [rax+rcx], ch   ; porównanie bajtu w %rax+rcx z górną granicą zakresu
    ja koniec                   ; jeśli jest większy, to koniec pętli
    sub byte ptr [rax+rcx], 0x20 ; konwersja małej
```

```ASM
movq %rax, %rdx    # Skopiuj wartość %rax do %rdx
andq $0xdf, %rdx   # Wyzeruj 6. bit, zamieniając małe litery na duże litery
movq %rdx, %rax    # Skopiuj zmienioną wartość do %rax
```

W powyższym kodzie wykorzystywane są trzy instrukcje:

movq %rax, %rdx - Kopiowanie wartości z rejestru %rax do %rdx.
andq $0xdf, %rdx - Wyzerowanie 6. bitu w rejestrze %rdx, co spowoduje zamianę małych liter na duże litery. Bit 6 odpowiada za wielkość litery w kodzie ASCII, gdzie wartość 32 (0x20) oznacza małą literę, a wartość 0 (0