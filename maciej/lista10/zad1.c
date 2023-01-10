#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define Pi 3.141593
#define stopnieNaRadiany(stopnie) ((stopnie) * Pi / 180.0)
#define promienZiemi 6371.0

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

double odleglosc(double lat1, double lon1, double lat2, double lon2){   //law of haversine
    double dLat = stopnieNaRadiany(lat2 - lat1);
    double dLon = stopnieNaRadiany(lon2 - lon1);

    lat1 = stopnieNaRadiany(lat1);
    lat2 = stopnieNaRadiany(lat2);

    double a = sin(dLat/2) * sin(dLat/2) + sin(dLon/2) * sin(dLon/2) * cos(lat1) * cos(lat2); 
    double c = 2 * atan2(sqrt(a), sqrt(1-a)); 
    
    return promienZiemi * c;
}

int main(int argc, char* argv[]){

    if(argc < 2){
        printf("Nieprawidlowa liczba argumentow wywolania");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");

    if(fp == NULL){
        printf("Blad przy otwieraniu pliku");
        return 2;
    }

    PtList* lista = NULL; 
    float f1, f2, f3;
    int elementy = 0;
    char nazwa[47], linia[256];

    while(fgets(linia, sizeof(linia), fp)){
        elementy++;
        sscanf(linia, "%f %f %f  %[^\n]", &f1, &f2, &f3, nazwa);
        if(strcmp(nazwa, "KONIEC") == 0){
            break;
        }
        stworz(&lista, f1, f2, f3, nazwa);
    }

    fclose(fp);

    if(argc ==2){
        wyswietl(lista);
        printf("Liczba wczytanych wszystkich elementow: %d", elementy);
    }

    if(argc == 3){
        for(PtList* licznik = lista; licznik != NULL; licznik = licznik->next){
            if(strstr(licznik->nazwa, argv[2])){
                printf("%f %f %f %s\n", licznik->x, licznik->y, licznik->z, licznik->nazwa);
            }
        }
    }

    if(argc == 4 && strcmp(argv[3], "dist") == 0){
        char* nazwa;
        double lat;
        double lon;
        for(PtList* licznik = lista; licznik != NULL; licznik = licznik->next){
            if(strstr(licznik->nazwa, argv[2])){
                nazwa = licznik->nazwa;
                lat = licznik->z;
                lon = licznik->y;
                break;
            }
        }
        
        for(PtList* licznik = lista; licznik != NULL; licznik = licznik->next){
            printf("%s -> %s : %.2f [km]\n", nazwa, licznik->nazwa, odleglosc(lat, lon, licznik->z, licznik->y));
        }
        
    }
    
    pamiec(&lista);

    return 0;
}
