//Maciej Styś lista2 zad2

#include<stdio.h>

float NumGet(int baza){
    char n, opr;
    float liczba1 = 0, liczba2 = 0;
    while(n != '\n' && n != '!'){
        n = getchar();
        if(n >= 48 && n < baza + 48){
            liczba1 += n - 48;
            liczba1 *= baza;
        }
        else if(baza == 16 && n >= 65 && n <= 70){
            liczba1 += n - 55;
            liczba1 *= baza;
        }
        if(n == '+' || n == '-' || n == '*' || n == '/' || n == '!'){
            opr = n;
            while(n != '\n'){
                n = getchar();
                if(n >= 48 && n < baza + 48){
                    liczba2 += n - 48;
                    liczba2 *= baza;
                }
                if(baza == 16 && n >= 65 && n <= 70){
                    liczba2 += n - 55;
                    liczba2 *= baza;
                }
            }
        }
    }
    liczba1 /= baza;
    liczba2 /= baza;
    if(opr == '+'){
        return liczba1 + liczba2;
    }
    else if(opr == '-'){
        return liczba1 - liczba2;
    }
    else if(opr == '*'){
        return liczba1 * liczba2;
    }
    else if(opr == '/'){
        return liczba1 / liczba2;
    }
    else if(opr == '!'){
        liczba2 = liczba1 - 1;
        while(liczba2 != 1){
            liczba1 *= liczba2;
            liczba2--;
        }
    }
    return liczba1;
}

void NumPut(int baza, int x){
    int liczba[32], y = 0;

    while(x){
        liczba[y] = x % baza;
        x /= baza;
        y++;
    }

    for(; y > 0; y--){
        if(baza == 16){
            if(liczba[y - 1] < 10){
                putchar(liczba[y - 1] + 48);
            }
            else{
                putchar(liczba[y - 1] + 55);
            }
        }
        else{
            putchar(liczba[y - 1] + 48);
        }
    }
    putchar(46);
}

int main(){
    int baza = 0, x;
    while(baza != 16 && (baza < 2 || baza > 10)){
        printf("Podaj baze: ");
        scanf("%d", &baza);
    }
    getchar();

    while(1){
        printf("Podaj wyrazenie w systemie %d: ", baza);
        x = NumGet(baza);
        if(!x){
            return 0;
        }
        NumPut(16, x);
        NumPut(10, x);
        printf("\n");
    }
}