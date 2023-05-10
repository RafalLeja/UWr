```C
/* mismatch-a.c */
void p2(void);      //slaby

int main() {        //silny
  p2();
  return 0;
}

/* mismatch-b.c */
#include <stdio.h>

char main;          //slaby
//char main = 'a';  -> multiple definitions of 'main'        

void p2() {         //silny
  //make = 21; -> Segmentation fault (core dumped)
  printf("0x%x\n", main);
}
```


    In C code, this option controls the placement of global variables defined without an initializer, known as tentative definitions in the C standard. Tentative definitions are distinct from declarations of a variable with the extern keyword, which do not allocate storage.

    The default is -fno-common, which specifies that the compiler places uninitialized global variables in the BSS section of the object file. This inhibits the merging of tentative definitions by the linker so you get a multiple-definition error if the same variable is accidentally defined in more than one compilation unit.

    The -fcommon places uninitialized global variables in a common block. This allows the linker to resolve all tentative definitions of the same variable in different compilation units to the same object, or to a non-tentative definition. This behavior is inconsistent with C++, and on many targets implies a speed and code size penalty on global variable references. It is mainly useful to enable legacy code to link without errors.
