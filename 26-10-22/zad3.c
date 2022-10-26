#include <stdio.h>

int main(void)
{
    int w, h, d, pora = 0;
    scanf("%d %d %d\n", &w, &h, &d);
    // printf("%d %d %d", w, h, d);
    char las[w][h];
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            scanf("%c ", &las[j][i]);
        }
        
    }

    
    int cien[w][h];
    for (int p = 0; p < 3; p++)
    {
        pora = p;
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                cien[j][i] = 0;
            }
            
        }
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                if (las[j][i] != '.')
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
                    
                    case 1:
                        for (int k = 1; k <= ((wys > i) ? i : wys); k++)
                        {
                            cien[j][i - k] = 1;
                        }
                        
                        break;

                    case 2:
                        for (int k = 1; k <= ((wys > (w-j)) ? (w-j) : wys); k++)
                        {
                            cien[j + k][i] = 1;
                        }
                        
                        break;

                    default:
                        break;
                    }
                }
            }
            
        }
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                if (las[j][i] != '.' && las[j][i] != '9')
                {
                    las[j][i] = las[j][i] + cien[j][i];
                    //printf("%d\n", cien[j][i]);
                }
                
            }
            
        }
        
    }
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            printf("%c", las[j][i]);
        }
        printf("\n");
        
    }
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