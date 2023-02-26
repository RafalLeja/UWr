#include<stdio.h>

void supply(int tab[45]){
    tab[0] = 1; tab[1] = 2;

    for(int x = 2; x <= 45; x++){
        tab[x] = tab[x - 1] + tab[x - 2];
    }
}

int main(){
    int fib[45], x, z = 0;

    supply(fib);
    
    scanf("%i", &x);
    
    for(int y = 44; y >= 0; y--){
        if(x >= fib[y]){
            printf("%c", '1');
            x -= fib[y];
            z = 1;
        }

        else if(z == 1){
            printf("%c", '0');
        }
    }

    return 0;
}