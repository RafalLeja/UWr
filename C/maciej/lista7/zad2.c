//Maciej Stys lista7 zad2

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

void usuwanieSpacji(char *ps){
    while(*ps == ' '){
        *ps = getchar();
    }
}

int przedzialDoSekund(char *ps){
    int sekundy = 0, temp = 0, war1, war2;
    *ps = getchar();
    while(*ps != ','){
        if(*ps != ':'){
        temp = temp * 10 + (int)(*ps) - 48;
        }
        else{
            sekundy = sekundy * 60 + temp;
            temp = 0;
        }
        *ps = getchar();
    }
    war1 = sekundy * 60 + temp;
    
    sekundy = 0; temp = 0;
    *ps = getchar();
    while(*ps != ']'){
        if(*ps != ':'){
        temp = temp * 10 + (int)(*ps) - 48;
        }
        else{
            sekundy = sekundy * 60 + temp;
            temp = 0;
        }
        *ps = getchar();
    }
    *ps = getchar();
    war2 = sekundy * 60 + temp;

    return war2 - war1;
}

int czasDoSekund(char *ps){
    usuwanieSpacji(ps);
    if(*ps == '['){
        return przedzialDoSekund(ps);
    }

    int sekundy = 0, temp = 0;
    while(*ps != ' ' && *ps != '\n'){
        if(*ps != ':'){
            temp = temp * 10 + (int)(*ps) - 48;
        }
        else{
            sekundy = sekundy * 60 + temp;
            temp = 0;
        }
        *ps = getchar();
    }

    return sekundy * 60 + temp;
}

void operator(char *ps, char *opr){
    usuwanieSpacji(ps);
    while(*ps != ' '){
            *opr = *ps;
            *ps = getchar();
        }
}


int main(){
    char s, opr;
    char *ps = &s, *popr = &opr;
    int war, wynik;

    while((s = getchar()) != EOF){
        wynik = czasDoSekund(ps);

        if(wynik == 0){
            return 0;
        }
        else if(wynik < 0){
            printf("zly przedzial");
            return 1;
        }

        while(s != '\n'){
            operator(ps, popr);
            war = czasDoSekund(ps);
            if(war < 0){
                printf("zly przedzial");
                return 1;
            }

            wynik = wykonaj(opr, wynik, war);
        }
        wypisz(wynik);
    }
    return 0;
}