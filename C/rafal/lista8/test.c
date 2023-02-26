#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drzewo.h"



int main()
{
    Drzewo tree = newDrzewo();
    pushDrzewo(tree, "A");
    printDrzewo(tree);
    delDrzewo(tree);
    return 0;
}
