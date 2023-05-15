```
gcc -ggdb -Og -Wall -g0 -fno-common -S -o data.s data.c


-ggdb -> Produce debugging information for use by GDB. This means to use the most expressive format available (DWARF, stabs, or the native format if neither of those are supported), including GDB extensions if at all possible. 
-Og -> Optimize debugging experience. -Og should be the optimization level of choice for the standard edit-compile-debug cycle, offering a reasonable level of optimization while maintaining fast compilation and a good debugging experience.
-Wall -> This enables all the warnings about constructions that some users consider questionable, and that are easy to avoid (or modify to prevent the warning), even in conjunction with macros. 
-fno-common -> The default is -fno-common, which specifies that the compiler places uninitialized global variables in the BSS section of the object file.
-S -> generuj plik asm
-o -> nazwa pliku wyjściowego
```

/usr/lib/gcc/x86_64-linux-gnu/10/cc1 -quiet -v -imultiarch x86_64-linux-gnu data.c -quiet -dumpbase data.c -mtune=generic -march=x86-64 -auxbase data -ggdb -Og -Wall -version -fasynchronous-unwind-tables -o /tmp/ccVTNnCh.s

```ASM
    .globl foo
    .data
    .align 2
    .type foo, @object
    .size foo, 2
foo:
    .value 314
    .section .rodata
    .type abc, @object
    .size abc, 4
abc:
    .string "abc"
    .globl bar
    .bss
    .align 8
    .type bar, @object
    .size bar, 8
bar:
    .zero 8
    .globl array
    .bss
    .align 32
    .type array, @object
    .size array, 800
array:
    .zero 800
    .globl some
    .data
    .align 32
    .type some, @object
    .size some, 38
some:
    .quad weird
    .long -3
    .zero 4
    .quad abc
    .quad foo
    .string "efghi"
```

.global 
    makes the symbol visible to ld. If you define symbol in your partial program, its value is made available to other partial programs that are linked with it. Otherwise, symbol takes its attributes from a symbol of the same name from another file linked into the same program. 

.data 
    tells as to assemble the following statements onto the end of the data subsection numbered subsection (which is an absolute expression). If subsection is omitted, it defaults to zero. 

.aligin 
    Pad the location counter (in the current subsection) to a particular storage boundary. The first expression (which must be absolute) is the alignment required, as described below. If this expression is omitted then a default value of 0 is used, effectively disabling alignment requirements. 

.type 
    This directive is used to set the type of a symbol
STT_OBJECT
object
    Mark the symbol as being a data object.

.size This directive is used to set the size associated with a symbol. 

.value expression1, expression2, ..., expressionN
    The .value directive generates an initialized word (16-bit, two's complement value) for each expression into the current section. Each expression must be a 16-bit integer value. The .value directive is not valid for the .bss section. 

.section name
    Use the .section directive to assemble the following code into a section named name. 

.string 
    Copy the characters in str to the object file. You may specify more than one string to copy, separated by commas. Unless otherwise specified for a particular machine, the assembler marks the end of each string with a 0 byte. You can use any of the escape sequences described in Strings.

.bss subsection
    .bss tells as to assemble the following statements onto the end of the bss section. For ELF based targets an optional subsection expression (which must evaluate to a positive integer) can be provided. In this case the statements are appended to the end of the indicated bss subsection. 

.quad bignums
    .quad expects zero or more bignums, separated by commas. For each bignum, it emits an 8-byte integer. If the bignum won’t fit in 8 bytes, it prints a warning message; and just takes the lowest order 8 bytes of the bignum.