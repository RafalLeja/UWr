```C
typedef struct {
        unsigned char   e_ident[EI_NIDENT]; //oznaczeniu pliku jako object file
        Elf64_Half      e_type;
        Elf64_Half      e_machine;          //architektura procesora
        Elf64_Word      e_version;          //numer wersji
        Elf64_Addr      e_entry;            //adres wejscia
        Elf64_Off       e_phoff;            //program header table's file offset
        Elf64_Off       e_shoff;            //section header table's file offset
        Elf64_Word      e_flags;            //flagi procesora
        Elf64_Half      e_ehsize;           //rozmiar headera
        Elf64_Half      e_phentsize;        //rozmiar elementu tablicy programu
        Elf64_Half      e_phnum;            //ilosc elementow tablicy programu
        Elf64_Half      e_shentsize;        //rozmiar elementu tablicy sekcji
        Elf64_Half      e_shnum;            //ilosc elementow tablicy sekcji
        Elf64_Half      e_shstrndx;         //indeks wejscia tablicy sekcj
} Elf64_Ehdr;


typedef struct {
	Elf64_Word	p_type;
	Elf64_Word	p_flags;
	Elf64_Off	p_offset;
	Elf64_Addr	p_vaddr;    //adres pierwszego bajtu
	Elf64_Addr	p_paddr;    //adres fizyczny
	Elf64_Xword	p_filesz;   //liczba bajtow obrazu pliku
	Elf64_Xword	p_memsz;    //liczba bajtow obrazu pamieci
	Elf64_Xword	p_align;
} Elf64_Phdr;
```
```
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 03 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - GNU
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x401520
  Start of program headers:          64 (bytes into file)
  Start of section headers:          3556304 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         10
  Size of section headers:           64 (bytes)
  Number of section headers:         38
  Section header string table index: 37

Program Headers:
  Type           Offset             VirtAddr           PhysAddr
                 FileSiz            MemSiz              Flags  Align
  LOAD           0x0000000000000000 0x0000000000400000 0x0000000000400000
                 0x0000000000000538 0x0000000000000538  R      0x1000
  LOAD           0x0000000000001000 0x0000000000401000 0x0000000000401000
                 0x000000000008f45d 0x000000000008f45d  R E    0x1000
  LOAD           0x0000000000091000 0x0000000000491000 0x0000000000491000
                 0x0000000000026026 0x0000000000026026  R      0x1000
  LOAD           0x00000000000b77b0 0x00000000004b87b0 0x00000000004b87b0
                 0x0000000000005ac0 0x000000000000b2f0  RW     0x1000
  NOTE           0x0000000000000270 0x0000000000400270 0x0000000000400270
                 0x0000000000000040 0x0000000000000040  R      0x8
  NOTE           0x00000000000002b0 0x00000000004002b0 0x00000000004002b0
                 0x0000000000000044 0x0000000000000044  R      0x4
  TLS            0x00000000000b77b0 0x00000000004b87b0 0x00000000004b87b0
                 0x0000000000000020 0x0000000000000068  R      0x8
  GNU_PROPERTY   0x0000000000000270 0x0000000000400270 0x0000000000400270
                 0x0000000000000040 0x0000000000000040  R      0x8
  GNU_STACK      0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000000 0x0000000000000000  RW     0x10
  GNU_RELRO      0x00000000000b77b0 0x00000000004b87b0 0x00000000004b87b0
                 0x0000000000003850 0x0000000000003850  R      0x1

 Section to Segment mapping:
  Segment Sections...
   00     .note.gnu.property .note.gnu.build-id .note.ABI-tag .rela.plt 
   01     .init .plt .text __libc_freeres_fn .fini 
   02     .rodata .eh_frame .gcc_except_table 
   03     .tdata .init_array .fini_array .data.rel.ro .got .got.plt .data __libc_subfreeres __libc_IO_vtables __libc_atexit .bss __libc_freeres_ptrs 
   04     .note.gnu.property 
   05     .note.gnu.build-id .note.ABI-tag 
   06     .tdata .tbss 
   07     .note.gnu.property 
   08     
   09     .tdata .init_array .fini_array .data.rel.ro .got 
```