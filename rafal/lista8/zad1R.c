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
        FILE * plik;
        //printf("\nplik = %s\n", argv[i]);
        if(argv[i][0] == '-'){
            plik = stdin;
        }else {
            plik = fopen(argv[i], "r");
        }
        char *str = strdup(""); 
        int l = 0;        
        
        while ((l = fgetc(plik)) != EOF)
        {
            if(!(l >= 'A' && l <= 'Z') && !(l >= 'a' && l <= 'z')){
                //printf("dasdsad");
                //printf("%s\n", str);
                if (str[0] != '\0')
                {
                    pushDrzewo(tree, str);
                }
                str = strdup("");
                continue;
            }else if(l > 'Z'){
                l = l - ('a' - 'A');
            }
            strcat(str, (char* ) &l);
            //printf("%c", l);
        }
        pushDrzewo(tree, str); 
        fclose(plik);
        free(str);       
    }
    printDrzewo(tree, "");
    delDrzewo(tree);
    return 0;
}
