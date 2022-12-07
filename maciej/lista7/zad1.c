//Maciej Stys lista7 zad1

#include <stdio.h>

int wykonaj(char opr, int war1, int war2){
    if(opr == '+'){
        return war1 + war2;
    }
    else if(opr == '-'){
        return war1 - war2;
    }
    else if(opr == '*'){
        return war1 * war2;
    }
    else{
        return war1/war2;
    }
}

void wypisz(int wynik){
    int godziny = wynik / 3600;
    int minuty = (wynik % 3600) / 60;
    int sekundy = wynik % 60;

    if(godziny != 0){
        printf("%d:%d:%d\n", godziny, minuty, sekundy);
    }
    else if(minuty != 0){
        printf("%d:%d\n", minuty, sekundy);
    }
    else{
        printf("%d\n", sekundy);
    }

}

int main(){
    char s, opr;
    int temp, war1 = 1, war2, oper;

    while(1){
        temp = 0; war1 = 0;
        while((s = getchar()) != ' ' && s != '\n' && s != EOF){
            if(s != ':'){
                temp = (temp * 10) + (int)(s) - 48;
            }
            else{
                war1 = war1 * 60 + temp;
                temp = 0;
            }
        }
        war1 = war1 * 60 + temp;

        if(war1 == 0){  //koniec programu
            return 0;
        }

        while(s != '+' && s !=  '-' && s != '*' && s != '/'){
            s = getchar();
        }

        opr = s;

        while((s = getchar()) == ' '){
        }

        temp = 0; war2 = 0;
        while(s != '\n'){
            if(s != ':'){
                temp = (temp * 10) + (int)(s) - 48;
            }
            else{
                war2 = war2 * 60 + temp;
                temp = 0;
            }
            s = getchar();
        }
        war2 = war2 * 60 + temp;

        oper = wykonaj(opr, war1, war2);

        wypisz(oper);
    }
    return 0;
}