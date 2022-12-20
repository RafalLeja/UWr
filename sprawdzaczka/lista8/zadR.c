#include <stdio.h>
#include <math.h>
#include "snoise.c"

int localMaxX[7000];
int localMaxY[7000];

float distance(int x1, int y1, int x2, int y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

float lowestDistance(int LMcount){
    float min = 8000;
    for (int i = 0; i < LMcount-1; i++)
    {
        for (int j = i+1; j < LMcount; j++)
        {
            float dist = distance(localMaxX[i], localMaxY[i], localMaxX[j], localMaxY[j]);
            if (min > dist)
            {
                min = dist;
            }
        }
    }
    return min;
}

int localMax(int x, int y, int k){
    float max = 0;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            float val = snoise2((x + j)*(1.0/k), (y + i)*(1.0/k));
            if (max < val)
            {
                max = val;
            } 
        }
    }
    if(max == snoise2(x*(1.0/k), y*(1.0/k))){
        return 1;
    }
    return 0;
};

int main(){
    int xres, yres, d, LMcount = 0;
    float k;
    scanf("%d %d %f %d", &xres, &yres, &k, &d);
    for (int i = 1; i < yres-1; i++)
    {
        for (int j = 1; j < xres-1; j++)
        {
            if(localMax(j, i, k) == 1){
                localMaxX[LMcount] = j;
                localMaxY[LMcount] = i;
                LMcount++;
            }
            //printf("%f", snoise2(j*(1.0/k), i*(1.0/k)));
        }
        //printf("\n");
    }
    printf("odbioriniki %d \nodleglosc %.1f", LMcount, lowestDistance(LMcount));
}