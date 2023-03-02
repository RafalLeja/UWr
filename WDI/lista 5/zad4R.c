#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int a = 1, b = 1, c = 1, p;
    for (int i = 2; i < n; i++)
    {
        p = a+b+c;
        a = b;
        b = c;
        c = p;
    }
    printf("%d", c);
}