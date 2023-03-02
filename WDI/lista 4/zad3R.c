#include <stdio.h>

int nwd(int a, int b){
    int k = 10;
    if (a < b)
    {
        k = b;
        b = a;
        a = k;
    }
    while (b > 0)
    {
        k = a % b;
        a = b;
        b = k;
    }
    return a;
    }

int main(){
    int n;
    scanf("%d", &n);
    int tab[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &tab[i]);
    }
    int wynik = tab[0];
    for (int i = 0; i < n-1; i++)
    {
        wynik = nwd(tab[i+1], wynik);
    }
    printf("%d", wynik);
}