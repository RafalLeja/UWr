//Maciej Styś lista2 zad1

#include<stdio.h>

int NumGet(int baza){
    char n;
    int liczba = 0;
    while(n != '.'){
        n = getchar();
        if(n >= 48 && n < baza + 48){
            liczba += n - 48;
            liczba *= baza;
        }
    }
    return liczba / baza;
}

void NumPut(int baza, int x){
    int liczba[32], y = 0;

    while(x){
        liczba[y] = x % baza;
        x /= baza;
        y++;
    }

    for(; y > 0; y--){
        putchar(liczba[y - 1] + 48);
    }
    putchar(46);
}

int main(){
    int baza, x;
    printf("Podaj baze: ");
    scanf("%d", &baza);
    while(1){
        printf("Podaj liczbe w systemie %d: ", baza);

        x = NumGet(baza);
        if(!x){
            return 0;
        }

        NumPut(2, x);
        NumPut(8, x);
        NumPut(10, x);
        printf("\n");
    }
}