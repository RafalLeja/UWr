#include <stdio.h>

int main(){
    int n, x, maks = 0, krok;
    scanf("%d", &n);
    int permutacje[n], liczby[n];

    for(int i = 0; i < n; i++){
        scanf("%d", &x);
        permutacje[i] = x;
        liczby[i] = 1;
    }

    for(int i = 0; i < n; i++){
        krok = 0;
        if(liczby[i]){
            x = permutacje[i];
            krok = 1;
            liczby[i] = 0;
            while(liczby[x - 1]){
                krok++;
                liczby[x - 1] = 0;
                x = permutacje[x - 1];
            }
            if(krok > maks){
                maks = krok;
            }
        }
    }

    printf("%d", maks);

    return 0;
}