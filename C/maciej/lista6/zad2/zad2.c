//Maciej Stys lista6 zad2

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Ksiazka_s{
    char autor[100];
    char tytul[100];
    int rok;
    int strony;
}Ksiazka;

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Nieprawidlowa ilosc danych na wejsciu");
        return 1;
    }
    
    FILE* plik;
    Ksiazka ksiazki[100];

    plik = fopen(argv[argc - 2], "r");

    int i = 0;
    char pom[12];
    char *ptr;
    while(fgets(ksiazki[i].autor, 100, plik) != NULL){
        ksiazki[i].autor[strcspn(ksiazki[i].autor, "\n")] = 0;
        
        fgets(ksiazki[i].tytul, 100, plik);
        ksiazki[i].tytul[strcspn(ksiazki[i].tytul, "\n")] = 0;
        fgets(pom, 12, plik);
        ksiazki[i].rok = strtol(pom, &ptr, 10);
        fgets(pom, 12, plik);
        ksiazki[i].strony = strtol(pom, &ptr, 10);

        i++;
    }

    fclose(plik);

    for(int j = 0; j < i; j++){
        printf("%s %s %d %d\n", ksiazki[j].autor, ksiazki[j].tytul, ksiazki[j].rok, ksiazki[j].strony);
    }

    return 0;
}