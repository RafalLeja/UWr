#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
//#include "svg.h"
#define WIDTH 600.0
#define HEIGHT 600.0

const double PI = 3.14159265358979323846;

typedef struct {
	double x;
	double y;
} Point;

void generateSide(FILE* plik, int degree, Point p1, Point p2,  int first);

void generateSnowflake(FILE* plik, int degree, int w, int h);

void generateCarpet(FILE * plik, int degree, Point p, int w);

void generateTriangle(FILE* plik, int degree, Point p1, Point p2, Point p3);

void pythagorasSquare(FILE* plik, int degree, Point p1, Point p2);

void pythagorasTriangle(FILE* plik, int degree, Point p1, Point p2, Point p3);

void generateMoorecurve(FILE* plik, int degree, int width, int height);

void rFunction(FILE * plik, int degree, Point *pen, double size, int obrot);

void lFunction(FILE * plik, int degree, Point *pen, double size, int obrot);

void forward(FILE * plik, Point *pen, double size, int obrot);

int main(int argc, char const *argv[]){
	int x = 500, y = 500;
	char typy[5][12] = {"snowflake","carpet","triangle","moorecurve","tree"};
	if (argc < 2)
	{
		printf("brak argumentow");
		return 1;
	}
	int draw = -1, degree = 0;
	FILE * plik = stdout;
	for (int i = 1; i < argc; i++)
	{
		if (argc % 2 == 0)
		{
			printf("bledna ilosc argumentow");
			return 1;
		}
				
		if (strcmp("--draw", argv[i]) == 0)
		{
			i++;
			for (int j = 0; j < 5; j++)
			{
				if (strcmp(typy[j], argv[i]) == 0)
				{
					draw = j;
					break;
				}
			}
			continue;
		}
		if (strcmp("--degree", argv[i]) == 0)
		{
			i++;
			degree = atoi(argv[i]);
			continue;
		}
			if (strcmp("--outfile", argv[i]) == 0)
			{
				i++;
				plik = fopen( argv[i], "w");
				continue;
			}
				
	}

	fprintf(plik, "<html>\n<body>\n<svg width=\"%f\" height=\"%f\" viewBox=\"%f %f\">\n", WIDTH, HEIGHT, WIDTH, HEIGHT);

	switch (draw)
	{
		case -1:
			printf("niepoprawny argument --draw \npolecenie powinno wygladac nastepujaco --draw [snowflake|carpet|triangle|moorecurve|tree]");
			return 1;
			break;
		
		case 0:
			generateSnowflake(plik, degree, x, y);
			break;

		case 1:
			Point p;
			p.x = 0;
			p.y = 0;
			generateCarpet(plik, degree, p, y);
			break;

		case 2:
			Point p1, p2, p3;
			p1.x = x/6;
			p1.y = y/6;
			p2.x = x*5/6;
			p2.y = y/6;
			p3.x = x/2;
			p3.y = y*5/6;
			generateTriangle(plik, degree, p1, p2, p3);
			break;

		case 3:
			generateMoorecurve(plik, degree, x, y);
			break;

		case 4:
			Point a = {x*2.5/6, y*5/6};
			Point b = {x*3.5/6, y*5/6};
			pythagorasSquare(plik, degree, a, b);
			break;
	}

	fprintf(plik, "</svg>\n </body>\n </html>");
	fclose(plik);

}

void generateSide(FILE* plik, int degree, Point p1, Point p2,  int first){
 
	if (degree == 0) {
		if (first == 1)
		{
			fprintf(plik, "M ");
		}else
		{
			fprintf(plik, "L ");
		}
		
		
		fprintf(plik, "%f %f L %f %f ", p1.x, p1.y, p2.x, p2.y);
	} else {
		Point p3, p4, p5;
		double angle = PI / 3.0;

		p3.x = (2.0 * p1.x + p2.x) / 3.0;
		p3.y = (2.0 * p1.y + p2.y) / 3.0;
		p5.x = (p1.x + 2.0 * p2.x) / 3.0;
		p5.y = (p1.y + 2.0 * p2.y) / 3.0;
		p4.x = p3.x + (p5.x - p3.x) * cos(angle) - (p5.y - p3.y) * sin(angle);
		p4.y = p3.y + (p5.x - p3.x) * sin(angle) + (p5.y - p3.y) * cos(angle);

		generateSide(plik, degree - 1, p1, p3, first == 1 ? 1 : 0);
		generateSide(plik, degree - 1, p3, p4, 0);
		generateSide(plik, degree - 1, p4, p5, 0);
		generateSide(plik, degree - 1, p5, p2, 0);
	} 
}

void generateSnowflake(FILE* plik, int degree, int w, int h){
	Point p1, p2, p3;
	p1.x = w/6;
	p1.y = h*5/6;
	p2.x = w*5/6;
	p2.y = h*5/6;
	p3.x = w/2;
	p3.y = h/6;

	fprintf(plik, "<path fill=\"white\" stroke=\"cyan\" stroke-width=\"5\" d=\"");
	generateSide(plik, degree, p1, p2, 1);
	generateSide(plik, degree, p2, p3, 0);
	generateSide(plik, degree, p3, p1, 0);
	fprintf(plik, "\"/>");
	return;
}

void generateCarpet(FILE * plik, int degree, Point p, int w){
	if (degree == 0) {
		fprintf(plik, "  <path stroke=\"white\" stroke-width=\"0\" d=\"M %f %f L %f %f L %f %f L %f %f Z\" fill=\"white\" />\n", p.x, p.y, p.x + w, p.y, p.x+w, p.y +w, p.x, p.y+w);
	} else {
		double newSize = w / 3.0;
		int i, j;

		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				if (i == 1 && j == 1) continue;

				Point newPoint;
				newPoint.x = p.x + j * newSize;
				newPoint.y = p.y + i * newSize;
				generateCarpet(plik, degree-1 , newPoint, newSize);
			}
		}
	}
}

void generateTriangle(FILE* plik, int degree, Point p1, Point p2, Point p3) {
	if (degree == 0) {
		fprintf(plik, "  <path stroke=\"white\" stroke-width=\"0\" d=\"M %f %f L %f %f L %f %f Z\" fill=\"blue\" />\n", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
	} else {
		Point p4, p5, p6;

		p4.x = (p1.x + p2.x) / 2.0;
		p4.y = (p1.y + p2.y) / 2.0;
		p5.x = (p2.x + p3.x) / 2.0;
		p5.y = (p2.y + p3.y) / 2.0;
		p6.x = (p1.x + p3.x) / 2.0;
		p6.y = (p1.y + p3.y) / 2.0;

		generateTriangle(plik, degree -1, p1, p4, p6);
		generateTriangle(plik, degree -1, p4, p2, p5);
		generateTriangle(plik, degree -1, p6, p5, p3);
	}
}

void pythagorasSquare(FILE* plik, int degree, Point p1, Point p2){
	if (degree < 0)
	{
		return;
	} else {
		Point p3, p4, p5;

		p3.x = p2.x - (p1.y - p2.y);
		p3.y = p2.y - (p2.x - p1.x);
		p4.x = p1.x - (p1.y - p2.y);
		p4.y = p1.y - (p2.x - p1.x);
		p5.x = p4.x + (p2.x - p1.x - (p1.y - p2.y)) /2;
		p5.y = p4.y - (p2.x - p1.x + p1.y - p2.y) /2;

		//fprintf(plik, "<path fill=\"rgb(%f,255,%f)\" d=\"M %f %f L %f %f L %f %f L %f %f Z\" /> \n", 255 - 255.0/(degree+1), 255-255.0/(degree+1), p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);
		fprintf(plik, "<path stroke=\"white\" stroke-width=\"0\" fill=\"rgb(%f,255,%f)\" d=\"M %f %f L %f %f L %f %f L %f %f Z\" /> \n", 255 - 255.0/(degree+1), 255-255.0/(degree+1), p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);
		//Point p4, p5, p6, p7, p8, p9;


		pythagorasTriangle(plik, degree, p4, p5, p3);


	}
	
}

void pythagorasTriangle(FILE* plik, int degree, Point p1, Point p2, Point p3){
	fprintf(plik, "<path stroke=\"white\" stroke-width=\"0\" fill=\"rgb(%f,255,%f)\" d=\"M %f %f L %f %f L %f %f Z\" /> \n", 255 - 255.0/(degree+1), 255 - 255.0/(degree+1), p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
	pythagorasSquare(plik, degree -1, p1, p2);
	pythagorasSquare(plik, degree -1, p2, p3);

}

void lFunction(FILE * plik, int degree, Point *pen, double size, int obrot){
	if (degree < 0)
	{
		return;
	}
	obrot -= 90;
	rFunction(plik, degree -1, pen, size, obrot);
	forward(plik, pen, size, obrot);
	obrot += 90;
	lFunction(plik, degree -1, pen, size, obrot);
	forward(plik, pen, size, obrot);
	lFunction(plik, degree -1, pen, size, obrot);
	obrot += 90;
	forward(plik, pen, size, obrot);
	rFunction(plik, degree -1, pen, size, obrot);
	obrot -= 90;
}

void rFunction(FILE * plik, int degree, Point *pen, double size, int obrot){
	if (degree < 0)
	{
		return;
	}
	obrot += 90;
	lFunction(plik, degree -1, pen, size, obrot);
	forward(plik, pen, size, obrot);
	obrot -= 90;
	rFunction(plik, degree -1, pen, size, obrot);
	forward(plik, pen, size, obrot);
	rFunction(plik, degree -1, pen, size, obrot);
	obrot -= 90;
	forward(plik, pen, size, obrot);
	lFunction(plik, degree -1, pen, size, obrot);
	obrot += 90;
}

void forward(FILE * plik, Point *pen, double size, int obrot){
	while (obrot > 270 || obrot < 0)
	{	
		if (obrot > 270)
		{
			obrot -= 360;
		}else if (obrot < 0)
		{
			obrot += 360;
		}
	}
	switch (obrot)
	{
	case 0:
		//fprintf(plik, "M %f %f ", pen->x, pen->y);
		pen->y -= size;
		fprintf(plik, "L %f %f \n", pen->x, pen->y);
		break;
	
	case 90:
		pen->x += size;
		fprintf(plik, "L %f %f \n", pen->x, pen->y);
		break;
	
	case 180:
		pen->y += size;
		fprintf(plik, "L %f %f \n", pen->x, pen->y);
		break;
	
	case 270: 
		pen->x -= size;
		fprintf(plik, "L %f %f \n", pen->x, pen->y);
		break;

	default:
		break;
	}
}

void generateMoorecurve(FILE* plik, int degree, int width, int height){
	fprintf(plik, "<path fill=\"transparent\" stroke=\"blue\" stroke-width=\"1\" d=\"\n");
	Point pen;
	int obrot = 0;
	int a = 0;
	for (int i = 0; i < degree; i++)
	{
		a = 2*a+1;
	}
	printf("%d / %d \n", a, 2*a+1);
	printf("%f  ", (a*(0.95*width))/(2*a+1) + 0.025*width);
	pen.x = (a*(0.95*width))/(2*a+1) + 0.025*width;
	pen.y = 0.975*height;
	double size = (0.95*width)/((a*2)+1);
	fprintf(plik, "M %f %f \n", pen.x, pen.y);

	lFunction(plik, degree -1, &pen, size, obrot);
	forward(plik, &pen, size, obrot);
	lFunction(plik, degree -1, &pen, size, obrot);
	obrot += 90;
	forward(plik, &pen, size, obrot);
	obrot += 90;
	lFunction(plik, degree -1, &pen, size, obrot);
	forward(plik, &pen, size, obrot);
	lFunction(plik, degree -1, &pen, size, obrot);
	fprintf(plik, "\" /> \n");
}
