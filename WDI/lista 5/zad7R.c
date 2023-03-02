#include <stdio.h>

int czasA = 0;
int czasB = 0;


int main(){
    int n,m;
    scanf("%d%d", &n,&m);
    long long int x = n;
    //int pot = n;
    int mnoznik = 1;
    while (x < m)
    {
        czasA++;
        x *= x;
        mnoznik*=2;
    }
    while (x/n > m)
    {
        czasB++;
        x/=n;
        mnoznik--;
    }
    
    printf("%lld %d %d %d", x, mnoznik, /*czasA > czasB ? czasA : czasB*/ czasA, czasB );
    
}