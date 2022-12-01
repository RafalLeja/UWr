//Maciej Stys lista6 zad1 funkcje

#include<stdio.h>
#include"operacje.h"

void wczytaj(char *napis){
    char s;
    s = getchar();
    char *p = napis;
    while((s >= 'a' && s <='z') || (s>= 'A' && s<='Z')){
        *p = s;
        p++;
        s = getchar();
    }
    *p = 0;
}

int palindrom(char *t){
    char *koniec = t;
    char *poczatek = t;

    while(*koniec){ //wyliczenie dlugosci napisu
        koniec++;
    }
    koniec--;

    while(koniec - poczatek >= 0){
        if(*koniec != *poczatek){ //nie palindrom
            return 0; 
        }
        koniec--;
        poczatek++;
    }

    return 1;
}

void reverse(char *t){
    char *koniec = t;
    char *poczatek = t;
    while(*koniec){
        koniec++;
    }
    koniec--;

    while(koniec - poczatek >= 0){
        char s = *poczatek;
        *poczatek = *koniec;
        *koniec = s;
        koniec--;
        poczatek++;
    }

    while(*t){
        printf("%c", *t);
        t++;
    }
}