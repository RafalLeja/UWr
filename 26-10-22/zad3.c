#include <stdio.h>

int ** symulacjaSlonca(int pora, int w, int h, char *las[][h]){
    int cien[w][h];
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (las[j][i] >= '0' && las[j][i] <= '9')
            {
                int wys = las[j][i] - 48;
                switch (pora)
                {
                case 0:
                    for (int k = 1; k <= ((wys > j) ? j : wys); k++)
                    {
                        cien[j - k][i] = 1;
                    }
                    
                    break;
                
                default:
                    break;
                }
            }
        }
        
    }

return cien[][];
}

int main(void)
{
    int w, h, d = 0;
    scanf("%d %d %d\n", &w, &h, &d);
    // printf("%d %d %d", w, h, d);
    char las[w][h];
    int cien[w][h];
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            scanf("%c ", &las[j][i]);
        }
        
    }
    cien = symulacjaSlonca(0, w, h, las[][])
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            printf("%d", cien[j][i]);
        }
        printf("\n");
        
    }

    
    return 0;
}
