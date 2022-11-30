#include<stdio.h>
#include<math.h>

int main(){

for(long long d = 0; d < 100000; d++){
    long long dk = d * d, a = 0, b = 0, c = 0;
    for(long long x = 1; x < d; x++){
        for(long long y = 1; y < d; y++){
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
        printf("%lld : BRAK\n", d);
    }
    else{
        printf("%lld : %lld %lld %lld\n", d, c, b ,a);
    }
}
return 0;
}