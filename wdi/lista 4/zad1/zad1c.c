#include <stdio.h>

int main(){
    int n, x;
    scanf("%d %d", &n, &x);
    int potX = x;
    int suma = x;
    for(int i = 2; i <= n; i++){
        potX *= x;
        suma += i*potX;
    }
    printf("%d", suma);
}