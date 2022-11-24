//Maciej Stys zad 2 lista 4

#include<stdio.h>
#include<math.h>

typedef unsigned short TypDaty;
unsigned short rk2, mies2, dzien2, tydz2;

char *dniTyg[] = {"pon", "wto", "sro", "czw", "pia", "sob", "nie"};

char *miesiac[] = {"styczen", "luty", "marzec", "kwiecien", "maj",
                   "czerwiec", "lipiec", "sierpien", "wrzesien", 
                   "pazdziernik", "listopad", "grudzien"};

char *rok[] = {"malpy", "koguta", "swini", "szczura", "tygrysa", "krolika",
               "smoka", "weza", "konia", "owcy", "kozy", "psa"};

unsigned short ZrobMiesiac(TypDaty data){
    unsigned short mies;
    mies = data >> 8;
    mies = mies << 12;               
    mies = mies >> 12;
    return mies;
}

unsigned short ZrobDzien(TypDaty data){
    unsigned short dzien;
    dzien = data >> 3;
    dzien = dzien << 11;
    dzien = dzien >> 11;
    return dzien;
}

unsigned short ZrobTydz(TypDaty data){
    unsigned short tydz;
    tydz = data << 13;
    tydz = tydz >> 13;
    return tydz;
}

int BladDaty(TypDaty data){
    unsigned short rk, mies, dzien, tydz;

    rk = data >> 12;
    mies = ZrobMiesiac(data);
    dzien = ZrobDzien(data);
    tydz = ZrobTydz(data);
                 
                            
    if(rk > 12 || rk == 0 || rk != rk2){
        return 1;
    }

    if(tydz > 7 || tydz == 0 || tydz != tydz2){
        return 1;
    }

    if(dzien > 31 || dzien == 0 || dzien != dzien2){
        return 1;
    }

    if(mies == 2 && dzien > 28){
        return 1;
    }

    if(mies > 12 || mies == 0 || mies != mies2){
        return 1;
    }

    if((mies == 4 || mies ==  6 || mies == 9 || mies == 11) && dzien > 30){
        return 1;
    }

    return 0;
}

void WypiszDate(TypDaty data){
    unsigned short rk, mies, dzien, tydz;

    rk = data >> 12;
    mies = ZrobMiesiac(data);
    dzien = ZrobDzien(data);
    tydz = ZrobTydz(data); 

    printf("%s %hu %s rok %s\n", dniTyg[tydz - 1], dzien, miesiac[mies - 1], rok[rk - 1]);
}

TypDaty ZrobDate(char dt, char d, char m, char rok){                                                             
    TypDaty data = 0;
    data = data | rok;
    data = data << 4;
    data = data | m;
    data = data << 5;
    data = data | d;
    data = data << 3;
    data = data | dt;

    return data;
}

int SkanowanieZmiennych(){
    scanf("%hu%hu%hu%hu", &tydz2, &dzien2, &mies2, &rk2);
    if(tydz2){
        return 0;
    }
    return 1;
}

int Odleglosc(TypDaty d1, TypDaty d2){
    int dni1 = 0, dni2 = 0;
    unsigned short rk, mies, dzien;

    rk = d1 >> 12;
    mies = ZrobMiesiac(d1);
    dzien = ZrobDzien(d1);

    dni1 = rk * 365;

    for(int i = 1; i <= mies; i++){
        if(i == 4 || i == 6 || 9 || i ==11 ){
            dni1 += 30;
        }
        else if(i == 2){
            dni1 += 28;
        }
        else{
            dni1 += 31;
        }
    }

    for(int i = 1; i <= dzien; i++){
        dni1++;
    }

    rk = d2 >> 12;
    mies = ZrobMiesiac(d2);
    dzien = ZrobDzien(d2);

    dni2 = rk * 365;

    for(int i = 1; i <= mies; i++){
        if(i == 4 || i == 6 || 9 || i == 11 ){
            dni2 += 30;
        }
        else if(i == 2){
            dni2 += 28;
        }
        else{
            dni2 += 31;
        }
    }

    for(int i = 1; i <= dzien; i++){
        dni2++;
    }

    return abs(dni1 - dni2);
}

int main(){
    TypDaty data1, data2;
    unsigned short blad1, blad2;

    while(1){
        blad1 = 0; blad2 = 0;
        if(SkanowanieZmiennych(dzien2, tydz2, mies2, rk2)){
            return 0;
        }

        data1 = ZrobDate((char) tydz2, (char) dzien2, (char) mies2, (char) rk2);
        blad1 = BladDaty(data1);
    
        if(SkanowanieZmiennych(dzien2, tydz2, mies2, rk2)){
            return 0;
        }

        data2 = ZrobDate((char) tydz2, (char) dzien2, (char) mies2, (char) rk2);
        blad2 = BladDaty(data2);


        if(!blad1 && !blad2){
            printf("%hu ", data1);
            WypiszDate(data1);

            printf("%hu ", data2);
            WypiszDate(data2);

            printf("%d\n", Odleglosc(data1, data2));
        }

        else if(blad1){
            printf("blad w pierwszej dacie\n");
        }

        else{
            printf("blad w drugiej dacie\n");
        }
    }
    return 0;
}