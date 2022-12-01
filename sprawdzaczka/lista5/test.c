#include<stdio.h>
#include<math.h>

int main(){

for(int d = 0; d < 100000; d++){
    long a = 0, b = 0, c = 0;
    long dk = d * d;

    for(int x = 1; x < d; x++){
        for(int y = 1; y < d; y++){
            if(x*x + y*y >= dk){
                break;
            }
            long z = dk - x*x - y*y;
            if(sqrt(z) - (int) sqrt(z) == 0){
                if(x * y * z >= a * b * c){
                    a = x; b = y; c = sqrt(z);
                }
            }
        }
    }

    if(!a){
        printf("%d : BRAK\n", d);
    }
    else{
        printf("%d : %ld %ld %ld\n", d, a, b ,c);
    }
}
    return 0;
}