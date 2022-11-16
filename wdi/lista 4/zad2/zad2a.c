#include <stdio.h>

int main(){
    int a, b = 0;
    scanf("%d %d", &a, &b);
    int nww = a*b;
    while (a != b)
    {
        if (a > b){
            a -= b;
        }else{
            b -= a;
        }
    }
    nww = nww/a;
    printf("%d, %d \n", a, b);
    printf("%d", nww);

}