#include<stdio.h>
#include "functions.h"

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("bledne wywolanie programu");
        return 1;
    }

    point* listOfPoints = getData(argv[1]);
    properties prop;
    prop = getProperties(listOfPoints);
    kilometer* kilometers = splitTrack(listOfPoints);

    showProp(prop);
    showKilo(kilometers);
    
    return 0;
}