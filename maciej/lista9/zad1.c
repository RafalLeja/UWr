#include<stdio.h>

int main(int argc, char* argv[]){
    int linie = 0, liczbaPunktow = 0, dlugoscTrasy = 0;
    long rozmiarPliku = 0;

    if(argc != 2){
        printf("Niepoprawna liczba argumentow");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");

    if(fp == NULL){
        printf("Blad przy otwieraniu pliku");
        return 2;
    }

    char linia[256];
    while(fgets(linia, sizeof(linia), fp)){
        linie++; //liczba lini

        if(strncmp(linia, "<trkpt", 6) == 0) {
            liczbaPunktow++;
        }

        int x = 0;       //rozmiar pliku
        while(linia[x] != '\0'){
            rozmiarPliku++;
            x++;
        }
    }

    fclose(fp);

    printf("dlugosc w bajtach: %d\nliczba wierszy: %ld\nliczba wczytanych punktow: %d", rozmiarPliku, linie, liczbaPunktow);
    return 0;
}