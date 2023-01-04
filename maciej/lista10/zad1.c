#include<stdio.h>

typedef struct PtList{
    float x;
    float y;
    float z;
    char nazawa[47];
    struct PtList *next;
}ptlist;


int main(int argc, char* argv[]){
    struct PtList *lis;
    lis = (struct PtList *) malloc(sizeof(struct PtList));

    if(argc < 2){
        printf("Niepoprawna liczba argumentow wywolania");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");

    if(fp == NULL){
        printf("Blad przy otwieraniu pliku");
        return 2;
    }





    return 0;
}