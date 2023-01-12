#include<stdio.h>
#include<stdlib.h>

int oblicz(int* a, int n, int x) {
    long long int wynik = a[0] % 1000000000;
    for(int i = 1; i <= n; i++) {
        wynik = (wynik * x + a[i]) % 1000000000;
    }
    return (int) llabs(wynik) % 100000;
}

int main(){
    int zestawy, maxX, x, buff;
    buff = scanf("%d", &zestawy);

    for(int a = 0; a < zestawy; a++){
        buff = scanf("%d %d", &maxX, &x);
        int wspolczynniki[maxX + 1];

        for(int b = 0; b <= maxX; b++){
            buff = scanf("%d", &wspolczynniki[b]);
        }
        
        printf("%05d\n", oblicz(wspolczynniki, maxX, x));
    }

    return buff;
}