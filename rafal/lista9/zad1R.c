#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]){
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

    //fprintf(plik, "<html> <body> <svg width=\"100\" height=\"100\"> <circle cx=\"50\" cy=\"50\" r=\"50\" stroke=\"green\" stroke-width=\4\" fill=\"red\" />");

    switch (draw)
    {
    case -1:
        printf("niepoprawny argument --draw \npolecenie powinno wygladac nastepujaco --draw [snowflake|carpet|triangle|moorecurve|tree]");
        return 1;
        break;
    
    case 0:
        generateSnowflake(degree);
        break;

    case 1:
        generateCarpet(degree);
        break;

    case 2:
        generateTriangle(degree);
        break;

    case 3:
        generateMoorecurve(degree);
        break;

    case 4:
        generateTree(degree);
        break;
    }

    fprintf(plik, "</svg> </body> </html>");
    fclose(plik);

}