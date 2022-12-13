#include <stdio.h>
#include "snoise.c"

int main(){
    int xres, yres, d;
    float k;
    scanf("%d %d %f %d", &xres, &yres, &k, &d);
    for (int i = 0; i < yres; i++)
    {
        for (int j = 0; j < xres; j++)
        {
            printf("%f", snoise2(j*(1.0/k), i*(1.0/k)));
        }
        printf("\n");
        
    }
    
}