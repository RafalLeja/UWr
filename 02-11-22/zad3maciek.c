#include <stdio.h>

int main(){
    int n, x, najw = 0, licznik;
    scanf("%d", &n);
    int permutacje[n], liczby[n];

    for(int i = 0; i < n; i++){
        scanf("%d", &x);
        permutacje[i] = x;
        liczby[i] = 1;
    }

    for(int i = 0; i < n; i++){
        licznik = 0;
        if(liczby[i]){
            x = permutacje[i];
            licznik = 1;
            liczby[i] = 0;
            while(liczby[x - 1]){
                licznik++;
                liczby[x - 1] = 0;
                x = permutacje[x - 1];
            }
            if(licznik > najw){
                najw = licznik;
            }
        }
    }

    printf("%d", najw);

    return 0;
}