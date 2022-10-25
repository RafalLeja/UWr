#include <stdio.h>

int symulacjaSlonca(int pora, char las[][], int w, int h){
    int cien[w][h];
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (las[j][i] >= '0' && las[j][i] <= '9')
            {
                wys = int(las[j][i]);
                switch (pora)
                {
                case 0:
                    for (int k = 0; k < ((wys > j) ? j : wys); k++)
                    {
                        /**/
                    }
                    
                    break;
                
                default:
                    break;
                }
            }
        }
        
    }
    

}

int main(void)
{
    int w, h, d, szyszki = 0;
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
        for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            printf("%c", las[j][i]);
        }
        printf("\n");
        
    }

    
    return 0;
}
