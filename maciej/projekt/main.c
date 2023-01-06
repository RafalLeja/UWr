#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct point{
    double lat;
    double lon;
    char time[20];
    struct point* next;
}point;

void join(point** list, point* newElement){
    if(*list == NULL){
        *list = newElement;
    }

    else{
        point* last = *list;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newElement;
    }
}

void createPoint(point** lista, double lat, double lon, char time[20]){
    point* new = (point*)malloc(sizeof(point));
    new->lat = lat;
    new->lon = lon;
    strcpy(new->time, time);
    new->next = NULL;
    join(lista, new);
}

point** getData(){
    FILE *fp = fopen("dane/rower.gpx", "r");
    point* points = NULL;
    point** start = &points;

    if(fp == NULL){
        printf("Blad przy otwieraniu pliku");
        return *start;
    }

    char line[256];
    while(fgets(line, sizeof(line), fp)){
        sscanf(line, " %[^\n]", line);
        if (strncmp(line, "<trkpt ", 7) == 0){
            double lat, lon;
            sscanf(line, "<trkpt lat=\"%lf\" lon=\"%lf\">", &lat, &lon);
        
            while(strncmp(line, "<time>", 6) != 0){
                fgets(line, sizeof(line), fp);
                sscanf(line, " %[^\n]", line);
            }

            char time[20];
            sscanf(line, "<time>%19[^<]</time>", time);

            createPoint(&points, lat, lon, time);
        }
    }

    return *start;
}

void wyswietl(point* list){
    for(point* counter = list; counter != NULL; counter = counter->next){
        printf("%f %f %s\n", counter->lat, counter->lon, counter->time);
    }
}









int main(int argc, char* argv[]){
    // if(argc < 2){
    //     printf("bledne wywolanie funkcji");
    //     return 1;
    // }

    point* listOfPoints = getData();

    wyswietl(listOfPoints);
    

    return 0;
}