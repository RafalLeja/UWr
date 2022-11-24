//Maciej Styś lista 1 zad 1

#include<stdio.h>

float check(float x, float d){
    float p = 0, z = x;

    while(x - p > 2 * d){
        if((x/2) * (x/2) == z){
            return x/2;
        }

        else if((p + (x - p)/2) * (p + (x - p)/2) > z){
            x = p + (x - p)/2;
        }

        else{
            p = p + (x - p)/2;
        }
    }
    return p + (x - p)/ 2;
}

int main(){
    float x, d;
    while(1){
        printf("\nPodaj liczbe: ");
        scanf("%f", &x);

        if(x == 1){
            return 0;
        }

        printf("Podaj dokladnosc: ");
        scanf("%f", &d);

        printf("%f", check(x, d));
    }
}