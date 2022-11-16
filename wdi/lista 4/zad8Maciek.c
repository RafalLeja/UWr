#include<stdio.h>

int cyfryx[10], cyfryy[10];
int main(){
    int x, y;
    scanf("%d%d", &x, &y);
    while(x && y){
        cyfryx[x % 10] += 1; x /= 10;
        cyfryy[y % 10] += 1; y /= 10;
    }

    if(x || y){
        printf("niepodobne");
        return 0;
    }

    for(int x = 0; x < 10; x++){
        if(cyfryx[x] != cyfryy[x]){
            printf("niepodobne");
            return 0;
        }
    }

    printf("podobne");
    return 0;
}