#include <stdio.h>

int main(){
    int w, h, n;
    char buff;
    buff = scanf("%d %d\n", &w, &h);
    char mapa[h][w];
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            buff = scanf("%c", &mapa[i][j]);
        }
        buff = scanf("%c\n", &buff);
    }
    buff = scanf("%d\n", &n);
    char wskazowki[n];
    for (int i = 0; i < n; i++)
    {
        buff = scanf("%c", &wskazowki[i]);
    }
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            if (mapa[y][x] != '.')
            {
                continue;
            }
            
            for (int obr = 0; obr < 4; obr++)
            {
                int posX = x, posY = y, rot = obr;
                int test = 0;
                for (int wzk = 0; wzk < n; wzk++)
                {
                    //printf("%c", wskazowki[wzk]);
                    int up = (rot == 0 ? 1 : 0); 
                    int right = (rot == 1 ? rot : 0);
                    int down = (rot == 2 ? 1 : 0); 
                    int left = (rot == 3 ? 1 : 0); 
                    char nextPos = mapa[posY - up + down][posX + right - left];
                    switch (wskazowki[wzk])
                    {
                        case 'S':
                        if (nextPos == '.' || nextPos == 'X')
                        {
                            posY = posY - up + down;
                            posX = posX + right - left;
                        }else {
                            test = 1;
                            break;
                        }
                        break;

                        case 'F':
                        while (nextPos == '.' || nextPos == 'X')
                        {
                            posY = posY - up + down;
                            posX = posX + right - left;
                            nextPos = mapa[posY - up + down][posX + right - left];
                        }
                        break;
        
                        case 'L':
                        rot--;
                        if (rot < 0)   
                        {
                            rot = 3;
                        }
                        break;

                        case 'R':
                        rot++; 
                        if (rot > 3)
                        {
                            rot = 0;
                        }
                        break;
                    }
                }
                if (test == 0)
                {
                    mapa[posY][posX] = 'X';
                }
            }
            
        }
        
    }
    
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            printf("%c", mapa[i][j]);
        }
        printf("\n");
    }
    
    
}