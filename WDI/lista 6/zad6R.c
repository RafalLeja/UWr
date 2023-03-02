#include<stdio.h>

#define x1 1, 1 
#define x2 x1, x1
#define x3 x2, x2
#define x4 x3, x3
#define x5 x4, x4
#define x6 x5, x5
#define x7 x6, x6
#define x8 x7, x7
#define x9 x8, x8
#define x10 x9, x9
#define x11 x10, x10
#define x12 x11, x11
#define x13 x12, x12


int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    int S[10000] = { x13, x10, x9, x8, x4};
    int pier[10000] = { x13, x10, x9, x8, x4};


    for(int i = 2; i * i <= n; i++){ //sprawdzanie liczb od 2 do pierwiastka z n
        if(pier[i] == 1){
            int x = 2 * i;
            while(x < n){           //wykreslanie kolejnych wielokrotnosci liczby pierwszej
                pier[x] = 0;
                x += i;
            }
        }
    }

    for (int i = m; i <= n; i++){
        for (int i = 0; pier[j] * pier[j] < i; i++)
        {
            if (i%pier[j]==0)
            {
                S[i-m] = 1;
                break;
            }
            
        }
        
    }
    


    for(int i = m; i < n; i++){     //wypisywanie liczb pierwszych od 2
        if(S[i]){
            printf("%d\n", i);
        }
    }

    return 0;
}