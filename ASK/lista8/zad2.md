.shstrtab
    This section holds section names.

.strtab
    This section holds strings, most commonly the strings that represent the names associated with symbol table entries. If the file has a loadable segment that includes the symbol string table, the section's attributes will include the SHF_ALLOC bit; otherwise, that bit will be off. 

```C
typedef struct {
	Elf64_Word	st_name;        //index nazwy symbolu
	unsigned char	st_info;    //typ i atrybuty wiazania
	unsigned char	st_other;   //widocznosc
	Elf64_Half	st_shndx;       //section header table index
	Elf64_Addr	st_value;       //wartosc
	Elf64_Xword	st_size;        //rozmiar
} Elf64_Sym;

typedef struct {
	Elf64_Word	sh_name;        //index nazwy symbolu
	Elf64_Word	sh_type;        //tym, semantyka
	Elf64_Xword	sh_flags;       //flagi
	Elf64_Addr	sh_addr;        //adres
	Elf64_Off	sh_offset;      //offset
	Elf64_Xword	sh_size;        //rozmiar
	Elf64_Word	sh_link;        //section header table index
	Elf64_Word	sh_info;        //dodatkowe info
	Elf64_Xword	sh_addralign;   //wartosc aligin
	Elf64_Xword	sh_entsize;     //rozmiar elementu tablicy
} Elf64_Shdr;
```

```
There are 15 section headers, starting at offset 0x3b0:

Section Headers:
  [Nr] Name
       Type              Address          Offset            Link
       Size              EntSize          Info              Align
       Flags
  [ 0] 
       NULL             0000000000000000  0000000000000000  0
       0000000000000000 0000000000000000  0                 0
       [0000000000000000]: 
  [ 1] .text
       PROGBITS         0000000000000000  0000000000000040  0
       0000000000000067 0000000000000000  0                 1
       [0000000000000006]: ALLOC, EXEC
  [ 2] .rela.text
       RELA             0000000000000000  0000000000000250  12
       00000000000000c0 0000000000000018  1                 8
       [0000000000000040]: INFO LINK
  [ 3] .data
       PROGBITS         0000000000000000  00000000000000a7  0
       0000000000000000 0000000000000000  0                 1
       [0000000000000003]: WRITE, ALLOC
  [ 4] .bss
       NOBITS           0000000000000000  00000000000000a8  0
       0000000000000010 0000000000000000  0                 8
       [0000000000000003]: WRITE, ALLOC
  [ 5] .rodata.str1.1
       PROGBITS         0000000000000000  00000000000000a8  0
       000000000000000a 0000000000000001  0                 1
       [0000000000000032]: ALLOC, MERGE, STRINGS
  [ 6] .data.rel
       PROGBITS         0000000000000000  00000000000000b8  0
       0000000000000008 0000000000000000  0                 8
       [0000000000000003]: WRITE, ALLOC
  [ 7] .rela.data.rel
       RELA             0000000000000000  0000000000000310  12
       0000000000000018 0000000000000018  6                 8
       [0000000000000040]: INFO LINK
  [ 8] .rodata.cst8
       PROGBITS         0000000000000000  00000000000000c0  0
       0000000000000008 0000000000000008  0                 8
       [0000000000000012]: ALLOC, MERGE
  [ 9] .comment
       PROGBITS         0000000000000000  00000000000000c8  0
       0000000000000013 0000000000000001  0                 1
       [0000000000000030]: MERGE, STRINGS
  [10] .note.GNU-stack
       PROGBITS         0000000000000000  00000000000000db  0
       0000000000000000 0000000000000000  0                 1
       [0000000000000000]: 
  [11] .note.gnu.property
       NOTE             0000000000000000  00000000000000e0  0
       0000000000000030 0000000000000000  0                 8
       [0000000000000002]: ALLOC
  [12] .symtab
       SYMTAB           0000000000000000  0000000000000110  13
       0000000000000108 0000000000000018  7                 8
       [0000000000000000]: 
  [13] .strtab
       STRTAB           0000000000000000  0000000000000218  0
       0000000000000032 0000000000000000  0                 1
       [0000000000000000]: 
  [14] .shstrtab
       STRTAB           0000000000000000  0000000000000328  0
       0000000000000088 0000000000000000  0                 1
       [0000000000000000]: 

Symbol table '.symtab' contains 11 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 SECTION LOCAL  DEFAULT    4 .bss
     2: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT    5 .LC1
     3: 0000000000000000    57 FUNC    LOCAL  DEFAULT    1 incr
     4: 0000000000000000     4 OBJECT  LOCAL  DEFAULT    4 count.0
     5: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT    8 .LC0
     6: 0000000000000008     8 OBJECT  LOCAL  DEFAULT    4 sum
     7: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND printf
     8: 0000000000000039    46 FUNC    GLOBAL DEFAULT    1 swap
     9: 0000000000000000     8 OBJECT  GLOBAL DEFAULT    6 bufp0
    10: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND buf
```