#include<stdio.h>
#include<stdlib.h>
#include<time.h>

unsigned int x, y, counter = 1;

void check(unsigned int x, unsigned int y, char opr){
    unsigned z = 101;
    if(opr == '-'){
        if(x > y){
            while(z != x - y){
            printf("\n%d - %d = ", x, y);
            scanf("%u", &z);
            }
        }      
        else{
            while(z != y - x){
                printf("\n%d - %d = ", y, x);
                scanf("%u", &z);
            }
        }
    }
    else{
        while(z != x + y){
            printf("\n%d + %d = ", x, y);
            scanf("%u", &z);
        }
    }
}


int main(){
    while(1){
        // printf("%02d:%02d:%02d", struct tm* localtime(time(NULL))->tm_hour, struct tm* localtime(time(NULL))->tm_min, struct tm* localtime(time(NULL))->tm_sec);
        printf("\nROUND %d", counter);
        srand(time(0));
        x = 100; y = 100;

        while(x + y > 100){
            x = rand() % 100 + 1;
            y = rand() % 100 + 1;
        }

        if(rand() % 2){
            check(x, y, '+');
        }
        else{
            check(x, y, '-');
        }
        counter ++;
    }

    return 0;
}