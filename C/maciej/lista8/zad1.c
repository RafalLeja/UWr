#include<stdio.h>

typedef struct Zespolon_{
    float rzecz;
    float uroj;
}Zespolon;

int main(int argc, char *argv[]){
    int szerokosc = 40, wysokosc = 25;
    Zespolon zespolon;
    zespolon.rzecz = 0.2; zespolon.uroj = 0.75;
    
    if(argc > 1){
        sscanf(argv[1], "%d", szerokosc);
        sscanf(argv[2], "%d", szerokosc);
        if(argc == 5){
            sscanf(argv[3], "%f", zespolon.rzecz);
            sscanf(argv[4], "%f", zespolon.uroj);
        }
    }
    

    return 0;
}