#include <stdio.h>
#include <string.h>
//#include "svg.h"
#define WIDTH 500.0
#define HEIGHT 500.0

void generateSnowflake(FILE* plik, int degree, int x, int y, int w, int h, int obrot){
    if (degree > 1)
    {
        return;
    }
    fprintf(plik, "<polygon points=\"%f,%f %f,%f %f,%f\" transform=\"translate(%d, %d) rotate(%d deg %d %d)\"/>\n", w/2.0, 0.0, 0.0, h*0.87, w*1.0, h*0.87, x, y, obrot, x, y);
    degree++;
    //generateSnowflake(plik, degree-1, x, y, w ,h);
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

    fprintf(plik, "<html>\n<body>\n<svg width=\"%f\" height=\"%f\">\n", WIDTH, HEIGHT);

    switch (draw)
    {
    case -1:
        printf("niepoprawny argument --draw \npolecenie powinno wygladac nastepujaco --draw [snowflake|carpet|triangle|moorecurve|tree]");
        return 1;
        break;
    
    case 0:
        generateSnowflake(plik, degree, x/2, y/2, WIDTH, HEIGHT, 0);
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