/* 
	* Rafał Leja
    * PO: lista 1, zadanie 2: ułamek
	* gcc ulamek.c 
*/
#include <stdio.h>
#include <stdlib.h>


typedef struct ulamek {
	int licz;
	int mian;
} Ulamek;

int NWD(int a, int b){
	int pom;
	while(b!=0){
		pom = b;
		b = a%b;
		a = pom;	
	}
	return a;
}

Ulamek * nowy_ulamek(int num, int denom){
	Ulamek *u = malloc(sizeof(Ulamek));
	int nwd = NWD(num, denom);
	u->licz = num / nwd;
	u->mian = denom / nwd;
	return u;
};

void show(Ulamek *u){
	printf("%d / %d = %f\n", u->licz, u->mian, 1.0*u->licz/u->mian);
}

Ulamek * dodaj_i_zwroc(Ulamek * a, Ulamek * b){
	Ulamek *out = nowy_ulamek(a->licz * b->mian + b->licz * a->mian, a->mian * b->mian);
	return out;
};

Ulamek * odejmij_i_zwroc(Ulamek * a, Ulamek * b){
	Ulamek *out = nowy_ulamek(a->licz * b->mian - b->licz * a->mian, a->mian * b->mian);
	return out;
};

Ulamek * pomnoz_i_zwroc(Ulamek * a, Ulamek * b){
	Ulamek *out = nowy_ulamek(a->licz * b->licz, a->mian * b->mian);
	return out;
};

Ulamek * podziel_i_zwroc(Ulamek * a, Ulamek * b){
	Ulamek *out = nowy_ulamek(a->licz * b->mian, a->mian * b->licz);
	return out;
};

void dodaj_i_zamien(Ulamek * a, Ulamek * b){
	b->licz = a->licz * b->mian + b->licz * a->mian;
	b->mian = a->mian * b->mian;
	int nwd = NWD(b->licz,b->mian);
	b->licz/= nwd;
	b->mian/= nwd;
};

void odejmij_i_zamien(Ulamek * a, Ulamek * b){
	b->licz = a->licz * b->mian - b->licz * a->mian;
	b->mian = a->mian * b->mian;
	int nwd = NWD(b->licz,b->mian);
	b->licz/= nwd;
	b->mian/= nwd;
};


void pomnoz_i_zamien(Ulamek * a, Ulamek * b){
	b->licz = a->licz * b->licz;
	b->mian = a->mian * b->mian;
	int nwd = NWD(b->licz,b->mian);
	b->licz/= nwd;
	b->mian/= nwd;
};


void podziel_i_zamien(Ulamek * a, Ulamek * b){
	int pom = b->licz;
	b->licz = a->licz * b->mian;
	b->mian = a->mian * pom;
	int nwd = NWD(b->licz,b->mian);
	b->licz/= nwd;
	b->mian/= nwd;
};

int main(){
	Ulamek *a = nowy_ulamek(1,2);
	Ulamek *b = nowy_ulamek(2,6);
	show(dodaj_i_zwroc(a,b));
	show(odejmij_i_zwroc(a,b));
	show(pomnoz_i_zwroc(a,b));
	show(podziel_i_zwroc(a,b));
	dodaj_i_zamien(a,b);
	show(b);
	odejmij_i_zamien(a,b);
	show(b);
	pomnoz_i_zamien(a,b);
	show(b);
	podziel_i_zamien(a,b);
	show(b);
	return 0; 
}
