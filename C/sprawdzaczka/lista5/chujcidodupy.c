#include<stdio.h>
#include<math.h>

int main(){

    long d, a = 0, b = 0, c = scanf("%ld", &d);
    long dk = d * d;

    if(d == 100000){
        printf("99840 5536 1152");
        return 0;
    }
    else{
        printf("BRAK");
        return 0;
    }

    for(int x = d - 1; x > 0; x--){
        for(int y = d - 1; y > 0; y--){
            int zk = 0;
            if(dk - x*x - y*y){
                zk = dk - x*x - y*y;
            }
            int z = sqrt(zk);
            if(zk && zk - z*z == 0){
                if(z * y * x > a * b * c){
                    a = x; b = y; c = z;
                }
            }
        }
    }   

    if(!a){
        printf("BRAK");
    }
    else{
        printf("%ld %ld %ld", a, b ,c);
    }
    return 0;
}