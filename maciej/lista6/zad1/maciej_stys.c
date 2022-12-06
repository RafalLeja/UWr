//Maciej Stys lista6 zad1

#include<stdio.h>
#include<stdlib.h>
#include"operacje.h"

int main(){
    char *napis;
    napis = (char*) malloc(101 * sizeof(char)); //zalokowanie pamieci

    wczytaj(napis);

    if(palindrom(napis)){
        printf("PALINDROM: ");
        wypisz(napis);
    }
    else{
        printf("REVERS: ");
        reverse(napis);
        wypisz(napis);
    }

    return 0;
}