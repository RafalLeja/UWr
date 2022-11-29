#include<stdio.h>
#include<math.h>

int main(){

    int d, a = 0, b = 0, c = scanf("%d", &d);
    long long dk = d * d;

    for(int x = 1; x < d; x++){
        for(int y = 1; y < d; y++){
            if(x*x + y*y >= dk){
                break;
            }
            long long z = dk - x*x - y*y;
            if(sqrt(z) - (int) sqrt(z) == 0){
                if(x * y * z >= a * b * c){
                    a = x; b = y; c = sqrt(z);
                }
            }
        }
    }

    if(!a){
        printf("BRAK");
    }
    else{
        printf("%d %d %d", a, b ,c);
    }

    return 0;
}