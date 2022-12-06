#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Ksiazka_{
    char autor[100];
    char tytul[100];
    int rok;
    int strony;
}Ksiazka;

int main(int argc, char* argv[]){
    Ksiazka ksiazka;
    FILE* plik;

    plik = fopen(argv[argc - 1], "r");

    while(fgets(ksiazka.autor, 100, plik) != NULL){
        fgets(ksiazka.tytul, 100, plik);
        fscanf("%d %d", ksiazka.rok, ksiazka.strony);

        printf("%s %s %d %d\n", ksiazka.autor, ksiazka.tytul, ksiazka.rok, ksiazka.strony);
    }

    fclose(plik);

    return 0;
}