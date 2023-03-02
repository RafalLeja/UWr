#include<stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    n++;
    int S[n];
    int W[10000];

    for(int i = 2; i < n; i++){     //wypelnienie sita jedynkami
        S[i] = 1;
        W[i] = 0;
    }

    for(int i = 2; i * i <= n; i++){ //sprawdzanie liczb od 2 do pierwiastka z n
        if(S[i] == 1){
            int x = 2 * i;
            while(x < n){           //wykreslanie kolejnych wielokrotnosci liczby pierwszej
                S[x] = 0;
                x += i;
            }
        }
    }
    int k = 0;
    for(int i = 2; i < n; i++){     
        if(S[i]){
            printf("%d,\n", i);
            W[k] = i;
            k++;
        }
    }
    int sum = 0;
    for (int i = 0; i < 10000; i++)
    {
        if (W[i] != 0)
        {
            sum += 1;
        }
        
    }
    printf("%d", sum);
    

    return 0;
}