//Maciej Styś lista1 zad2

#include<stdio.h>

int trojkat(int a, int b, int c){
    if(!(a > 0 && b > 0 && c > 0)){             //poprawnosc wprowadzonych liczb
        return 0;
    }
    if(a + b > c && a + c > b && b + c > a){    //warunek istnienia trojkata
        return 2;
    }
    return 1;
}

int prostokatny(int a, int b, int c){
    if(a * a == b * b + c * c || b * b ==  a * a + c * c || c * c == a * a + b * b){
        return 1;
    }
    return 0;
}

int prostokatny_a(int a, int b, int c){
    if(a * a == b * b + c * c){             //trojkat prostokatny z przeciwprostokatna a
        return 1;
    }
    return 0;
}


int main(){
    int a, b, c;
    printf("Podaj 3 liczby calkowite: ");
    scanf("%d%d%d", &a, &b, &c);

    if(!trojkat(a, b, c)){
        printf("Podano liczbe ujemna");
        return 0;
    }
    else if(trojkat(a, b, c) == 2){
        if(prostokatny(a, b, c)){
            printf("Podane liczby tworza trojkat prostokatny");
            return 0;
        }
    }

    for(b = 1; b < a; b++){
        for(c = 1; c < a; c++){
            if(prostokatny_a(a, b, c)){
                printf("Te liczby tworza trojka prostokatny: %d %d %d", a, b, c);
                return 0;
            }
        }
    }

    printf("Nie mozna stworzyc trojkata prostokatnego z przeciwprostokatna %d", a);
 
    return 0;
}