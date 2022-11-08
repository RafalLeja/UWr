#include <stdio.h>

int main(){
    int n, k, x, najw = 0;
    scanf("%d%d", &n, &k);
    int liczby[k], potegi[k];
    for(int i = 0; i < k; i++){
        scanf("%d", &x);
        liczby[i] = x;
        potegi[i] = 0;
    }

    for(int i = 0; i < k; i++){
        if(n % liczby[i] == 0){
            int y = liczby[i], licznik = 0;
            while(n % y == 0){
                licznik ++;
                y *= liczby[i];
            }
            potegi[i] = licznik;
            if(licznik > najw){
                najw = licznik;
            }
        }
    }

    printf("%d ", najw);

    for(int i = 0; i < k; i++){
        if(potegi[i] == najw){
            printf("%d ", liczby[i]);
        }
    }

    return 0;
}