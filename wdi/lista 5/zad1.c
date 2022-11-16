#include <stdio.h>

int pot(int a, int b){
    int rez = 1;
    while (b>0)
    {
        if (b%2)
        {
            rez *= a;
        }
        b /=2;
        a *= a;
        
    }
    return rez;
}

int potRek(int a, int b)
{
if (!b){
    return 1;
}    
if (b%2){
    return a* pot(a*a,b/2);
}
return pot(a*a, b/2);
}

int main()
{
    int k, b;
    scanf("%d", &k);
    b = pot(2,k);
    printf("%d|%d", pot(k,b), potRek(k,b));
    return 0;
}
