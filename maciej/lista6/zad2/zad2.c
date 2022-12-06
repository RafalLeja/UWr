#include <stdio.h>
#include <string.h>

typedef struct Ksiazka_{
    char autor[100];
    char tytul[100];
    char rok[12];
    char strony[12];
}Ksiazka;

int main(){
    Ksiazka ksiazka;
    FILE* plik;

    plik = fopen("test.txt", "r");

    fgets(ksiazka.autor, 100, plik);
    fgets(ksiazka.tytul, 100, plik);
    fgets(ksiazka.rok, 12, plik);
    fgets(ksiazka.strony, 12, plik);

    printf("%s %s %s %s", ksiazka.autor, ksiazka.tytul, ksiazka.rok, ksiazka.strony);
    fflush(stdout);

    fclose(plik);

    return 0;
}