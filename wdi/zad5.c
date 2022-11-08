#include <stdio.h>

int main(){
    int n, mnoznik = 1;
    scanf("%d", &n);
    while(mnoznik <= n){
        mnoznik *= 2;
    }

    mnoznik /= 2;
    int x = n, m = 0;
    while(x){
        if(x % 2){
            m += mnoznik;
        }
        x /= 2;
        mnoznik /= 2;
    }

    if(m == n){
        printf("palindrom");
    }
    else{
        printf("chuj ci do dupy");
    }

    return 0;
}