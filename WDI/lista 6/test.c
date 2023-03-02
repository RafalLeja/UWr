#include<stdio.h>

#define x1 1, 1 
#define x2 x1, x1
#define x3 x2, x2
#define x4 x3, x3
#define x5 x4, x4
#define x6 x5, x5
#define x7 x6, x6
#define x8 x7, x7
#define x9 x8, x8
#define x10 x9, x9
#define x11 x10, x10
#define x12 x11, x11
#define x13 x12, x12

int main(){
    int tab[10000] = { x13, x10, x9, x8, x4};
    int sum = 0;
    for (int i = 0; i < 10000; i++)
    {
        sum += tab[i];
    }
    printf("%d", sum);
    
}