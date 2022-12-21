#include <stdio.h>
#include <math.h>
#include "simplexnoise.c"

int localMaxX[7000];
int localMaxY[7000];

float distance(int x1, int y1, int x2, int y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

float lowestDistanceExept(int LMcount, int idx, int Eidx){
    float min = 8000;
    for (int j = 0; j < LMcount; j++)
    {
        if (localMaxX[j] < 0 || j == Eidx){
            continue;
        }   
        float dist = distance(localMaxX[idx], localMaxY[idx], localMaxX[j], localMaxY[j]);
        if (min > dist)
        {
            min = dist;
        }
    }
    return min;
}

float lowestDistance(int LMcount){
    float min = 8000;
    for (int i = 0; i < LMcount-1; i++)
    {
        if (localMaxY[i] < 0)
        {
            continue;
        }
        for (int j = i+1; j < LMcount; j++)
        {
            if (localMaxY[j] < 0){
                continue;
            }   
            float dist = distance(localMaxX[i], localMaxY[i], localMaxX[j], localMaxY[j]);
            if (min > dist)
            {
                min = dist;
            }
        }
    }
    return min;
}

void deleteClosest(int LMcount){
    float min = 8000;
    int idx1 = 0, idx2 = 0;
    for (int i = 0; i < LMcount-1; i++)
    {
        if (localMaxY[i] < 0)
        {
            continue;
        }
        for (int j = i+1; j < LMcount; j++)
        {
            if (localMaxY[j] < 0){
                continue;
            }   
            float dist = distance(localMaxX[i], localMaxY[i], localMaxX[j], localMaxY[j]);
            if (min > dist)
            {
                idx1 = i;
                idx2 = j;
                min = dist;
            }
        }
    }
    if (lowestDistanceExept(LMcount, idx1, idx2) > lowestDistanceExept(LMcount, idx2, idx1))
    {
        localMaxX[idx2] = -1;
        localMaxY[idx2] = -1;
        return;
    }else {
        localMaxX[idx1] = -1;
        localMaxY[idx1] = -1;
        return;
    }
    
}

int localMaxCounter(int x, int y, int k){
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
    int a = scanf("%d %d %f %d", &xres, &yres, &k, &d);
    a++;
    for (int i = 1; i < yres-1; i++)
    {
        for (int j = 1; j < xres-1; j++)
        {
            if(localMaxCounter(j, i, k) == 1){
                localMaxX[LMcount] = j;
                localMaxY[LMcount] = i;
                LMcount++;
            }
        }
    }
    printf("%d %.1f ", LMcount, lowestDistance(LMcount));
    for (int i = 0; i < d+1; i++)
    {
        deleteClosest(LMcount);
    }
    printf("%d %.1f", LMcount-d, lowestDistance(LMcount));
}