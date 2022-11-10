#include <stdio.h>

int tabN[10];
int tabM[10];
int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    while (n != 0 && m != 0)
    {
        tabN[n % 10] += 1;
        n /= 10;
        tabM[m % 10] += 1;
        m /= 10;
    }
    if (n != m){
        printf("nie");
        return 0;
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