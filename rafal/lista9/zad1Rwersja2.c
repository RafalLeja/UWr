#include <stdio.h>
#include <string.h>
#include <math.h>
//#include "svg.h"
#define WIDTH 600.0
#define HEIGHT 600.0

const double PI = 3.14159265358979323846;
typedef struct {
	double x;
	double y;
} Point;

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
		fprintf(plik, "  <path d=\"M %f %f L %f %f L %f %f L %f %f Z\" fill=\"white\" />\n", p.x, p.y, p.x + w, p.y, p.x+w, p.y +w, p.x, p.y+w);
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
		fprintf(plik, "  <path d=\"M %f %f L %f %f L %f %f Z\" fill=\"blue\" />\n", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
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

void generateTree(FILE* plik, int degree, double angle, double size, Point p1){
	if (degree < 0)
	{
		return;
	} else {

		Point p2, p3, p4, p1p, p2p, p3p;
		p2.x = p1.x + size;
		p2.y = p1.y;
		p3.x = p1.x + size;
		p3.y = p1.y + size;
		p4.x = p1.x - size * sin(angle);
		p4.y = p1.y + size * cos(angle);

		p1p.x = (p1.x - p4.x)*cos(angle)-(p1.y-p4.y)*sin(angle)+p4.x;
		p1p.y = (p1.x - p4.x)*sin(angle)+(p1.y-p4.y)*cos(angle)+p4.y;
		p2p.x = (p2.x - p4.x)*cos(angle)-(p2.y-p4.y)*sin(angle)+p4.x;
		p2p.y = (p2.x - p4.x)*sin(angle)+(p2.y-p4.y)*cos(angle)+p4.y;
		p3p.x = (p3.x - p4.x)*cos(angle)-(p3.y-p4.y)*sin(angle)+p4.x;
		p3p.y = (p3.x - p4.x)*sin(angle)+(p3.y-p4.y)*cos(angle)+p4.y;


		fprintf(plik, "<path fill=\"rgb(%f,255,%f)\" d=\"M %f %f L %f %f L %f %f L %f %f Z\" /> \n", 255 - 255.0/(degree+1), 255-255.0/(degree+1), p1p.x, p1p.y, p2p.x, p2p.y, p3p.x, p3p.y, p4.x, p4.y);
		//fprintf(plik, "<path fill=\"rgb(%f,255,%f)\" transform=\"rotate(%f %f %f)\" d=\"M %f %f L %f %f L %f %f L %f %f Z\" /> \n", 255 - 255.0/(degree+1), 255-255.0/(degree+1), angle*180/PI, p4.x, p4.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);
		//Point p4, p5, p6, p7, p8, p9;

		Point p6;
		double size2 = size / sqrt(2);
		double angle2 = angle - (PI/4);

		p6.x = p1.x + size2 * sin(angle2);
		p6.y = p1.y - size2 * cos(angle2);
		// if(degree <4){
		// 	angle+=PI/6;
		// }
		generateTree(plik, degree -1, angle2, size2, p6);


	}
	
}

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
			degree = argv[i][0] - '0';
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
			//generateMoorecurve(degree, x, y);
			break;

		case 4:
			p1.x = x*2/6;
			p1.y = y*4/6;
			// p2.x = x*4/6;
			// p2.y = y*5/6;
			// p3.x = x/2;
			// p3.y = y*7/12;
			generateTree(plik, degree, 0.0, 100.0, p1);
			break;
	}

	fprintf(plik, "</svg>\n </body>\n </html>");
	fclose(plik);

}