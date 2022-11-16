#include <stdio.h>

int main(){
    int n, mnoznik = 1, pot = 1;
    scanf("%d%d", &n, &pot);
    while(mnoznik <= n){
        mnoznik *= pot;
    }

    mnoznik /= pot;
    int x = n, m = 0;
    while(x){
        if(x % pot){
            m += mnoznik * (x % pot);
        }
        x /= pot;
        mnoznik /= pot;
    }

    if(m == n){
        printf("palindrom");
    }
    else{
        printf("nie");
    }

    return 0;
}