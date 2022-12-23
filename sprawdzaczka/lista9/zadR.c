#include <stdio.h>

int testClues(char wzkazowki, int n){
    for (int i = 0; i < n; i++)
    {
        switch (wzkazowki[i])
        {
        case 'F':
            testF()
            break;
        
        default:
            break;
        }
    }
    
}

int main(){
    int w, h, n;
    char buff;
    scanf("%d %d\n", &w, &h);
    char mapa[h][w];
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            scanf("%c", &mapa[i][j]);
        }
        scanf("%c\n", &buff);
    }
    scanf("%d\n", &n);
    char wzkazowki[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%c", &wzkazowki[i]);
    }

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            for (int i = 0; i < 4; i++)
            {
                for (int i = 0; i < n; i++)
                {
                    switch (wzkazowki[i])
                    {
                        case 'F':
                        testF();
                        break;
        
                        default:
                        break;
                    }
                }
                
            }
            
        }
        
    }
    
    for (int i = 0; i < n; i++)
    {
        printf("%c", wzkazowki[i]);
    }
    
    
}