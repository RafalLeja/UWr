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

void generateTriangle(FILE* plik, int degree, Point p1, Point p2,  int first){
 
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

    generateTriangle(plik, degree - 1, p1, p3, first == 1 ? 1 : 0);
    generateTriangle(plik, degree - 1, p3, p4, 0);
    generateTriangle(plik, degree - 1, p4, p5, 0);
    generateTriangle(plik, degree - 1, p5, p2, 0);
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
    generateTriangle(plik, degree, p1, p2, 1);
    generateTriangle(plik, degree, p2, p3, 0);
    generateTriangle(plik, degree, p3, p1, 0);
    fprintf(plik, "\"/>");
    return;
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
        //generateCarpet(degree, x, y);
        break;

    case 2:
        //generateTriangle(degree, x, y);
        break;

    case 3:
        //generateMoorecurve(degree, x, y);
        break;

    case 4:
        //generateTree(degree, x, y);
        break;
    }

    fprintf(plik, "</svg>\n </body>\n </html>");
    fclose(plik);

}