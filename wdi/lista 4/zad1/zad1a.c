#include <stdio.h>

int main(){
    int n = 0;
    scanf("%d", &n);
    n = n%2?-n:n;
    printf("%i", n); 
}