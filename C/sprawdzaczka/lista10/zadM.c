#include<stdio.h>
#include<stdlib.h>

int horner(int* a, int n, int x) {
    long long int wynik = a[0] % 1000000000;
    for(int i = 1; i <= n; i++) {
        wynik = (wynik * x + a[i]) % 1000000000;
    }
    return (int) llabs(wynik) % 100000;
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
        
        printf("%05d\n", horner(wspolczynniki, stopienWielomianu, x));
    }

    return buf;
}