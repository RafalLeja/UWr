#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drzewo.h"

int main(int argc, char const *argv[])
{
    Drzewo tree = newDrzewo();
    if(argc < 2){
        printf("brak argumentow wywolania");
    }
    for (int i = 1; i < argc; i++)
    {

        printf("plik = %s\n", argv[i]);
        FILE* plik = fopen(argv[i], (char*) 'r');
        char str[1]; 
        str[0] = fgetc(plik);
        //int idx = 0;
        char l;
        while (!feof(plik))
        {
            l = fgetc(plik);
            if(l == ' '){
                pushDrzewo(tree, str);
                printf("%s", str);
                str[0] = '\0';
                continue;
            }else if(l > 'Z'){
                l = l - ('a' - 'A');
            }
            strncat(str, &l, 1);
        }
        pushDrzewo(tree, str);        
    }
    
    return 0;
}
