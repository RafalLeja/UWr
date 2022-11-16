#include <stdio.h>

int main(){
    int n = 0;
    float suma = 0;
    scanf("%d", &n);
    float dzielnik = 0;
    for (int i = 1; i <= n; i++)
    {
        dzielnik = (i%2?-1:1);
        suma += dzielnik/i;
        //printf("%d \n", dzielnik/i);
        //suma += 1;
    }
    printf("%f", suma);
}