//Maciej Stys lista3 zad2

#include <stdio.h>

int x = 0, y, znacznik = 0, start = 0;
char s = 1;

int main(){
    while((s = getchar()) != EOF){
        if(s == '{'){
            start = 1;
            putchar(s);
            x++;
        }

        else if(s == '}'){
            start = 1;
            x--;
            putchar(s);
            if(x == 1){
                printf("    //tu powinien byc komentarz zawierajacy deklaracje funkcji ale nie udalo mi sie tego zrobic");
            }
        }

        else if((s == ' ' || s == '\t') && start){
            putchar(s);
        }

        else if (s == '\n'){
            putchar(s);
            start = 0;
            y = x - 1;
            while(y > 0){
                printf("    ");
                y--;
            }
        }

        else if(s != ' ' && s != '\t'){
            if(!start && x){
                printf("    ");
            }
            putchar(s);
            start = 1;
        }
    }

    return 0;
}