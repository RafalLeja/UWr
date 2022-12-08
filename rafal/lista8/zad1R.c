#include <stdio.h>
#include <stdlib.h>
#include "drzewo.h"

int main(int argc, char const *argv[])
{
    if(argc < 2){
        printf("brak argumentow wywolania");
    }
    for (int i = 1; i < argc; i++)
    {

        printf("plik = %s\n", argv[i]);
        FILE* plik = fopen(argv[i], 'r');
        while (1)
        {
            char l = fgetc(plik);
            switch (expression)
            {
            case /* constant-expression */:
                /* code */
                break;
            
            default:
                break;
            }
            
        }
        

    }
    
    return 0;
}
