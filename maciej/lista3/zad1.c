//Maciej Stys lista3 zad1

#include <stdio.h>

int x = 0;
char s = 1;

int main(){
    printf("%d ", x);
    while((s = getchar()) != EOF){
        if(s == '\n'){
            putchar('\n');
            printf("%d ", x);
        }
        else{
            putchar(s);

            if(s == '{'){
                x++;
            }
            else if(s == '}'){
                x--;
                if(x < 0){
                printf("\nBLAD");
                return 0;
                }
            }
        }
    }
    printf("\n%d", x);

    return 0;
}