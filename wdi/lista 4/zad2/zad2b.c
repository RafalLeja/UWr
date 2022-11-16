#include <stdio.h>

int main(){
    int a, b = 0;
    scanf("%d %d", &a, &b);
    int x = a;
    int y = b;
    while (a != b)
    {
        if (a > b){
            a -= b;
        }else{
            b -= a;
        }
    }
    x = x/a;
    y = y/a;
    printf("%d/%d \n", x, y);
}