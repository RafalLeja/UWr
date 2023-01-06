#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdio.h>

#define Pi 3.141593
#define stopnieNaRadiany(stopnie) ((stopnie) * Pi / 180.0)
#define promienZiemi 6371.0

double odleglosc(double lat1, double lon1, double lat2, double lon2){   //law of haversine
    double dLat = stopnieNaRadiany(lat2 - lat1);
    double dLon = stopnieNaRadiany(lon2 - lon1);

    lat1 = stopnieNaRadiany(lat1);
    lat2 = stopnieNaRadiany(lat2);

    double a = sin(dLat/2) * sin(dLat/2) + sin(dLon/2) * sin(dLon/2) * cos(lat1) * cos(lat2); 
    double c = 2 * atan2(sqrt(a), sqrt(1-a)); 
    
    return promienZiemi * c * 1000;
}

int main(int argc, char* argv[]){
    int wczytaneLinie = 0, liczbaPunktow = 0;
    double dystans = 0;
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
    double wspol[4];
    while(fgets(linia, sizeof(linia), fp)){
        wczytaneLinie++;

        if (strncmp(linia, "<trkpt ", 7) == 0){
            if(liczbaPunktow % 2 == 0){
                sscanf(linia, "<trkpt lat=\"%lf\" lon=\"%lf\">", &wspol[0], &wspol[1]);
            }
            else{
                sscanf(linia, "<trkpt lat=\"%lf\" lon=\"%lf\">", &wspol[2], &wspol[3]);
            }

            if(liczbaPunktow > 0){
                dystans += odleglosc(wspol[0], wspol[1], wspol[2], wspol[3]);
            }

            liczbaPunktow++;
        }

        int x = 0;
        while(linia[x] != '\0'){
            rozmiarPliku++;
            x++;
        }
    }

    fclose(fp);

    printf("dlugosc w bajtach: %ld\nliczba wierszy: %d\nliczba wczytanych punktow: %d\ndystans: %lf [m]", rozmiarPliku, wczytaneLinie, liczbaPunktow, dystans);
    return 0;
}