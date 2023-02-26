#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n, wynik, odp, wrg, a, b, x = 0;
int r = 1;

int main(void)
{   
    srand(time(NULL));
    printf("na ilu cyfrowych liczbach chcesz pracować? \n");
    if(!scanf("%d", &n)){
        printf("podaj liczbe całkowitą");
        return 0;
        }
    while (1 > 0)
    {
        for(int i; i < n; i++){
            r *= 10;
        }
        if(wrg){}else{
        x = (rand()%2);
        a = rand()%r;
        b = rand()%r;
        }
        if(x){
            if (a>b){
                printf("Oblicz: %d - %d\n", a, b);
                wynik = a - b;
            } else {   
                printf("Oblicz: %d - %d\n", b, a);
                wynik = b - a;            
            }
        } else {
            printf("Oblicz: %d + %d\n", a, b);
            wynik = a + b;
        }
        if(!scanf("%d", &odp)){
        printf("podaj liczbe całkowitą");
        return 0;
        }
        if(odp==wynik){
            wrg = 0;
        } else {
            wrg = 1;
        }
    }
    return 0;
}
