# include <stdio.h>
# include <math.h>

int n = 0;
float dist = 0;
float x, y = 0;
float fX, fY = 0;
float oldX, oldY = 0;

int main(void){
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        if(!i){
            scanf("%f %f", &fX, &fY);
            oldX = fX;
            oldY = fY;
        } else {
        scanf("%f %f", &x, &y);
        dist += sqrt((x - oldX)*(x - oldX) + (y - oldY)*(y - oldY));
        oldX = x;
        oldY = y;
        }
    }
    dist += sqrt((x - fX)*(x - fX) + (y - fY)*(y - fY));
    printf("%f", dist);    
    return 0;
}