#include<stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    n++;
    int S[n];

    for(int i = 2; i < n; i++){     //wypelnienie sita jedynkami
        S[i] = 1;
    }

    for(int i = 2; i * i < n; i++){ //sprawdzanie liczb od 2 do pierwiastka z n
        if(S[i]){
            int x = 2 * i;
            while(x < n){           //wykreslanie kolejnych wielokrotnosci liczby pierwszej
                S[x] = 0;
                x += i;
            }
        }
    }

    for(int i = 2; i < n; i++){     //wypisywanie liczb pierwszych od 2
        if(S[i]){
            printf("%d\n", i);
        }
    }

    return 0;
}