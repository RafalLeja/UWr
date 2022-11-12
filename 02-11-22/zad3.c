#include <stdio.h>

int main(){
    int n, max;
    scanf("%d", &n);
    int tab[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &tab[i]);
    }
    for (int i = 0; i < n; i++)
    {
        int krok = 0;
        int L = tab[i];
        int P = tab[L-1];
        while (P != (i+1))
        {
            P = tab[L-1];
            L = tab[P-1];
            krok++;
        }
        if (krok > max){
            max = krok;
        }
        
    }
    printf("%d", max);
    return 0;
}