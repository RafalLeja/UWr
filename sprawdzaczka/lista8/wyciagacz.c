#include <stdio.h>
#include <stdlib.h>

int main(){
    int xres, yres, d;
    float k;
    int a = scanf("%d %d %f %d", &xres, &yres, &k, &d);
    fprintf(stderr, "%d %d %f %d", xres, yres, k, d);
    a++;
    return 0;
}