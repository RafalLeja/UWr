#include <stdio.h>

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    int tabN[10] = {0,0,0,0,0,0,0,0,0,0};
    int tabM[10] = {0,0,0,0,0,0,0,0,0,0};
    while (n != 0)
    {
        if (n == 0){
            break;
        }
        int cyfra = n%10;
        //printf("%d", cyfra);
        tabN[cyfra] += 1;
        n = (n - cyfra)/10;
        cyfra = m%10;
        tabM[cyfra] += 1;
        m = (m - cyfra)/10;
    }
    int palindrom = 0;
    for (int i = 0; i < 10; i++){
        printf("%d, %d; - %d\n", tabN[i], tabM[i], i);
        if (tabN[i] != tabM[i])
        {
            palindrom = 1;
        }
    }
    if (palindrom)
    {
        printf("nie");
    }else {
        printf("tak");
    }
    
    return 0;
    }