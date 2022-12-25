#include <stdio.h>
#include <string.h>
#include <math.h>
//#include "svg.h"
#define WIDTH 500.0
#define HEIGHT 500.0

void generateTriangle(FILE* plik, int degree, int x, int y, int h, int obr){
    if (degree < 0){
        return;
    }
    int a = 2*(sqrtf(3)*h)/3;
    if (obr == 1)
    {
        fprintf(plik, "M %f %f L %f %f L %f %f L %f %f", x*1.0, y+(h/3.0), x+(a/2.0), y-(h*2/3.0), x-(a/2.0), y-(h*2/3.0), x*1.0, y+(h/3.0));
        return;
    }
        fprintf(plik, "M %f %f L %f %f L %f %f L %f %f", x*1.0, y-(h*2.0/3.0), x+(a/2.0), y+(h/3.0), x-(a/2.0), y+(h/3.0), x*1.0, y-(h*2.0/3.0));
    
}

void generateSnowflake(FILE* plik, int degree, int x, int y, int h, int obrot){
    int a = 2*(sqrtf(3)*h)/3;
    if (degree < 0)
    {
        return;
    }
    fprintf(plik, "<path d=\"");
    fprintf(plik, "M %f %f L %f %f L %f %f L %f %f ", x*1.0, y-(h*2.0/3.0), x+(a/2.0), y+(h/3.0), x-(a/2.0), y+(h/3.0), x*1.0, y-(h*2.0/3.0));
    generateTriangle(plik, degree, x/2, y-h/6, h/3, 1);
    generateTriangle(plik, degree, x+x/2, y/1.28, h/3, 1);
    generateTriangle(plik, degree, x, y+h-2*h/3, h/3, 1);
    fprintf(plik, "\" fill=\"red\" transform=\"");
    fprintf(plik, "rotate(%d %d %d)\"/>\n", obrot, x, y);
    // generateSnowflake(plik, degree-1, x/2, y/1.5, h/3, obrot - 60);
    // generateSnowflake(plik, degree-1, x+(a/3), y-(h/4), h/2.5, obrot + 60); 
    // generateSnowflake(plik, degree-1, x, y+(4.5*h/10), h/2.5, obrot + 180);
    return;
}

void generatePath(FILE*plik, int degree, int x, int y, int h, int obrot){
    int a = 2*(sqrtf(3)*h)/3;
    if (degree < 0)
    {
        return;
    }
    fprintf(plik, "<path d=\"");
    fprintf(plik, "M %f %f L %f %f L %f %f Z \"", x*1.0, y-(h*2.0/3.0), x+(a/2.0), y+(h/3.0), x-(a/2.0), y+(h/3.0));
    fprintf(plik, " fill=\"blue\" transform=\"");
    fprintf(plik, "rotate(%d deg %d %d)\"/>\n", obrot, x, y);

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
        generateSnowflake(plik, degree, x/2, y/2, 350, 0);
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