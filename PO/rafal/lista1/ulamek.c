/* 
	* Rafał Leja
        * PO: lista 1, ułamek
	* gcc ulamek.c -o ulamek && ./ulamek.exe
*/
#include <stdio.h>
#include <stdlib.h>


typedef struct ulamek {
	int licz;
	int mian;
} Ulamek;

Ulamek * nowy_ulamek(int num, int denom){
	Ulamek *u = malloc(sizeof(Ulamek));
	u->licz = num;
	u->mian = denom;
	return u;
};

void show(Ulamek *u){
	printf("%d / %d = %f\n", u->licz, u->mian, 1.0*u->licz/u->mian);
}

Ulamek * dodaj_i_zwroc(Ulamek * a, Ulamek * b){
	Ulamek *out = nowy_ulamek(a->licz * b->mian + b->licz * a->mian, a->mian * b->mian);
	return out;
};

int main(){
	Ulamek *a = nowy_ulamek(1,4);
	Ulamek *b = nowy_ulamek(1,3);
	show(dodaj_i_zwroc(a,b));
	return 1; 
}
