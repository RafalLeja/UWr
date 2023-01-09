#include<stdio.h>
#include<stdlib.h>

long int horner(int* a, int n, int x) {
    long int wynik = a[0] % 100000;
    for (int i = 1; i <= n; i++) {
        wynik = (wynik * x + a[i]) % 100000;
    }
    return wynik;
}

int main(){
    int liczbaZestawow, stopienWielomianu, x, buf;
    buf = scanf("%d", &liczbaZestawow);

    for(int a = 0; a < liczbaZestawow; a++){
        buf = scanf("%d %d", &stopienWielomianu, &x);
        int wspolczynniki[stopienWielomianu + 1];

        for(int b = 0; b <= stopienWielomianu; b++){
            buf = scanf("%d", &wspolczynniki[b]);
        }
        
        if(buf == -123){
            printf(" ");
        }     

        printf("%.5ld\n", labs(horner(wspolczynniki, stopienWielomianu, x)));
    }

    return 0;
}