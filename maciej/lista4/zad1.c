//Maciej Stys zad 1 lista 4

#include<stdio.h>

typedef unsigned short TypDaty;
unsigned short rk, mies, dzien, tydz;
TypDaty data;

char *dniTyg[] = {"pon", "wto", "sro", "czw", "pia", "sob", "nie"};

char *miesiac[] = {"styczen", "luty", "marzec", "kwiecien", "maj",
                   "czerwiec", "lipiec", "sierpien", "wrzesien", 
                   "pazdziernik", "listopad", "grudzien"};

char *rok[] = {"malpy", "koguta", "swini", "szczura", "tygrysa", "krolika",
               "smoka", "weza", "konia", "owcy", "kozy", "psa"};


int BladDaty(TypDaty data){

    rk = data >> 12;
    
    mies = data >> 8;
    mies = mies << 12;
    mies = mies >> 12;
    
    dzien = data >> 3;
    dzien = dzien << 11;
    dzien = dzien >> 11;
    
    tydz = data << 13;
    tydz = tydz >> 13;                 
                            
    if(rk > 12 || rk == 0){
        return 1;
    }

    if(tydz > 7 || tydz == 0){
        return 1;
    }

    if(dzien > 31 || dzien == 0){
        return 1;
    }

    if(mies == 2 && dzien > 28){
        return 1;
    }

    if(mies > 12 || mies == 0){
        return 1;
    }

    if((mies == 4 || mies ==  6 || mies == 9 || mies == 11) && dzien > 30){
        return 1;
    }

    return 0;
}

void WypiszDate(){
    printf("%s %hu %s rok %s\n", dniTyg[tydz - 1], dzien, miesiac[mies - 1], rok[rk - 1]);
}

int main(){
    scanf("%hd", &data);
    while(data && !feof(stdin)){
        if(BladDaty(data)){
            printf("komunikat\n");
        }

        else{
            WypiszDate(data);
        }
        scanf("%hd", &data);
    }

    return 0;
}