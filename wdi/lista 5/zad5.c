#include <stdio.h>

int fTrec(int n, int m){
    printf("T(%d, %d)\n", n, m);
    if (n ==0 || m == 0)
    {
        if (n>=m)
        {
            return n;
        }
        return m;        
    }
    return (fTrec(n-1, m) + (2*fTrec(n,m-1)));
}

int fTiter(int n, int m){
    for (int i = 0; i < n+m; i++)
    {

    }
    
    return n+m;
}

int main(){
    int n,m;
    scanf("%d%d", &n, &m);
    printf("%d\n%d", fTrec(n,m), fTiter(n,m));
}