#include <stdio.h>

int pot(int a, int n){
    for (int i = 0; i < n; i++)
    {
        a *=a;
    }
    return a;
}

int main(){
    int n;
    scanf("%d", &n);
    //int tab[n];
    //int i = n;
    // while(n){
    //     tab[i] = n%2;
    // }

    printf("%d", pot(2,6));
    
}