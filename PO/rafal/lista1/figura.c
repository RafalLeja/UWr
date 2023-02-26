/* 
	* Rafał Leja
        * PO: lista 1, zadanie 1: figura
	* gcc figura.c -o figura && ./figura.exe
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159

typedef enum {
	SQUARE = 0,
	TRIANGLE = 1,
	CIRCLE = 2
} Shape;

typedef struct figura {
	Shape typfig;
	float size;
	float x;
	float y;
} Figura;

Figura * new_square(float x, float y, float size){
	if (size <= 0) {
		fprintf(stderr, "Rozmiar musi być dodatni!\n");
		exit(1);
	}
	Figura *f = malloc(sizeof(Figura));
	f->size = size;
	f->x = x;
	f->y = y;
	f->typfig = SQUARE;
	return f;
};

Figura *new_circle(float x, float y, float size){
	if (size <= 0) {
		fprintf(stderr, "Rozmiar musi być dodatni!\n");
		exit(1);
	}

	Figura *f = malloc(sizeof(Figura));
	f->size = size;
	f->x = x;
	f->y = y;
	f->typfig = CIRCLE;
	return f;
};

Figura *new_triangle(float x, float y, float size){
	if (size <= 0) {
		fprintf(stderr, "Rozmiar musi być dodatni!\n");
		exit(1);
	}
	Figura *f = malloc(sizeof(Figura));
	f->size = size;
	f->x = x;
	f->y = y;
	f->typfig = TRIANGLE;
	return f;
};

float pole(Figura *f){
	float out;
	switch (f->typfig){
		case TRIANGLE:
			out = powf(f->size, 2)*sqrt(3)/4;
		break;

		case SQUARE:
			out = powf(f->size, 2);
		break;

		case CIRCLE:
		 	out = powf(f->size, 2) * PI;
		break;
	}
	return out;
};

void przesun(Figura *f, float x, float y){
	f->x += x;
	f->y += y;
};

void show(Figura *f){
	char typy[3][8] = {"triangle", "square", "circle"};
	printf("typ: %s; X: %f; Y: %f;\n", typy[(int) f->typfig], f->x, f->y);
};

float sumapol(Figura* f[], int size){
	float out = 0;
	for (int i = 0; i<size; i++) {
		out += pole(f[i]);
	}
	return out;
};

int main(){

	Figura *f = new_triangle(1.0, 1.5, 5);
	show(f);
	printf("%f\n", pole(f));
	return 0;
}
