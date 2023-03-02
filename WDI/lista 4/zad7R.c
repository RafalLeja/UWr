#include <stdio.h>

int main(){
    int n, k;
    scanf("%d", &n);
    int tabN[10] = {0,0,0,0,0,0,0,0,0,0};
    while (n != 0)
    {
        int cyfra = n%10;
        tabN[cyfra] += 1;
        n = (n - cyfra)/10;
    }
    for (int i = 0; i < 10; i++)
    {
        if (tabN[i] > 0){
            k++;
        }
    }
    printf("%d", k);
    return 0;
    }