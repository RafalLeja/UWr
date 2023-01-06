#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct PtList{
    float x;
    float y;
    float z;
    char nazwa[47];
    struct PtList *next;
}PtList;

void polacz(PtList** lista, PtList* nowyElement){
    if(*lista == NULL){
        *lista = nowyElement;
    }

    else{
        for(PtList* licznik = *lista; licznik != NULL; licznik = licznik->next){
            if(licznik->next == NULL){
                licznik->next = nowyElement;
                break;
            }
        }
    }
}

void stworz(PtList** lista, float a, float b, float c, char nazwaa[47]){
    PtList* nowy = (PtList*)malloc(sizeof(PtList));
    nowy->x = a;
    nowy->y = b;
    nowy->z = c;
    strcpy(nowy->nazwa, nazwaa);
    nowy->next = NULL;
    polacz(lista, nowy);
}

void wyswietl(PtList* lista){
    for(PtList* licznik = lista; licznik != NULL; licznik = licznik->next){
        printf("%f %f %f %s\n", licznik->x, licznik->y, licznik->z, licznik->nazwa);
    }
}

void pamiec(PtList** lista){
    for(PtList* licznik = *lista; licznik != NULL; licznik = licznik->next){
        free(licznik);
    }
}

int main(int argc, char* argv[]){

    if(argc < 2){
        printf("Niepoprawna liczba argumentow wywolania");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");

    if(fp == NULL){
        printf("Blad przy otwieraniu pliku");
        return 2;
    }

    PtList* lista = NULL; 
    float f1, f2, f3;
    char nazwa[47], linia[256];

    while(fgets(linia, sizeof(linia), fp)){
        sscanf(linia, "%f %f %f  %[^\n]", &f1, &f2, &f3, nazwa);
        if(strcmp(nazwa, "KONIEC") != 0){
            stworz(&lista, f1, f2, f3, nazwa);
        }
        else{
            break;
        }
    }
    fclose(fp);

    wyswietl(lista);
    pamiec(&lista);

    return 0;
}
