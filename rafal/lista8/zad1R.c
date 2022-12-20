#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drzewo.h"



int main(int argc, char const *argv[])
{
    Drzewo tree = newDrzewo();
    if(argc < 2){
        fprintf(stderr, "brak argumentow wywolania");
    }
    for (int i = 1; i < argc; i++)
    {
        FILE * plik;
        if(argv[i][0] == '-'){
            plik = stdin;
        }else {
            plik = fopen(argv[i], "r");
        }
        if (plik == NULL)
        {
            fprintf(stderr, "BLAD OTWARCIA PLIKU: \"%s\"\n", argv[i]);
        }
        
        char *str = strdup(""); 
        int l = 0;        
        
        while ((l = fgetc(plik)) != EOF)
        {
            if(!(l >= 'A' && l <= 'Z') && !(l >= 'a' && l <= 'z')){
                pushDrzewo(tree, str);

                str = strdup("");
                continue;
            }else if(l > 'Z'){
                l = l - ('a' - 'A');
            }
            strcat(str, (char* ) &l);
        }
        pushDrzewo(tree, str); 
        fclose(plik);
        free(str);       
    }
    printDrzewo(tree, "");
    delDrzewo(tree);
    return 0;
}
