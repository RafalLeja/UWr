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