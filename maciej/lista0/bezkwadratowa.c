#include<stdio.h>
#include<math.h>

int check(int num){
    for(int x = 2; x <= sqrt(num); x++){
        if(num % (x * x) == 0){
            return 0;
        }
    }
    return 1;
}

int main(){
    int x;
    scanf("%d", &x);

    for(x = x; x <= x + 1000; x++){
        if(check(x)){
            printf("%d", x);
            return 0;
        }
    }
    printf("BRAK");
    return 0;
}