#include<stdio.h>
#include<math.h>

int main(){

    long long d, a = 0, b = 0, c = scanf("%lld", &d);
    long long dk = d * d;

    for(int x = d - 1; x > 0; x--){
        for(int y = d - 1; y > 0; y--){
            long long zk = 0;
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
        printf("%lld %lld %lld", a, b ,c);
    }
    return 0;
}