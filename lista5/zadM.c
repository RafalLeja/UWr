#include<stdio.h>
#include<math.h>

int main(){

    long long d, a = 0, b = 0, c = scanf("%lld", &d);
    long long dk = d * d;

    for(long long x = sqrt(dk/4); x < d; x++){
        for(long long y = x; y < d; y++){
            long long zk = dk - x*x - y*y;
            if(zk <= 0){
                break;
            }
            long long z = sqrt(zk);
            if(zk - z*z == 0){
                if(x * y * z > a * b * c){
                    a = x; b = y; c = z;
                }
            }
        }
    }

    if(a == 0){
        printf("BRAK");
    }
    else{
        printf("%lld %lld %lld", c, b ,a);
    }
    return 0;
}