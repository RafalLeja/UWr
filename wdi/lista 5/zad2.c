#include <stdio.h>

int czas = 0;

int main(){
    int n;
    scanf("%d",&n);
    int tab[n];
    int pot = 0;
    int sil = 1;
    for (int i = 1; i < n+1; i++)
    {
        tab[i] = sil;
        if (tab[i] > n)
        {
            pot = i-1;
            break;
        }
        sil *= i;
        czas++;
    }
    for (int i = 0; i < pot-1; i++)
    {
        printf("%d", (n/tab[pot-i]));
        n -= (n/tab[pot-i])*tab[pot-i];
    }
    
    
    printf("\n%d", czas);

}