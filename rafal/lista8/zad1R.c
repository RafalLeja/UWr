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

        printf("\nplik = %s\n", argv[i]);
        FILE* plik = fopen(argv[i], "r");
        char *str = strdup(""); 
        int l = 0;        
        
        while ((l = fgetc(plik)) != EOF)
        {
            printf("%c", l);
            if(l == ' '){
                //printf("dasdsad");    
                pushDrzewo(tree, str);
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
    
    return 0;
}
