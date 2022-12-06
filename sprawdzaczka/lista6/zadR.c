#include <stdio.h>
#include <math.h>

char plyty[15][20][20];
char sklejka[20][20];

void rotate(int id, int n){
    char temp[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp[i][j] = plyty[id][i][j];
        }
        
    }
        for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            plyty[id][j][i] = temp[i][j];
        }
        
    }
    
}

void sklej(int n, int k){
    int sciana = 0;
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {
            for (int id = 0; id < k; id++)
            {
                if(plyty[id][x][y] == '#'){
                    sciana++;
                    break;
                }
            }
            if (sciana > 0)
            {
                sklejka[x][y] = '#';
            }else{
                sklejka[x][y] = '.';
            }
            sciana = 0;
            
        }
        
    }
    
}

int sprawdz(int n){
    int dziury = 0;
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {
            if (sklejka[x][y] == '.')
            {
                dziury++;
            }
            
        }
        
    }
    return dziury;
}

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    char temp;
    scanf("%c", &temp);
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int x = 0; x < n; x++)
            {
                scanf("%c", &plyty[i][j][x]);
                if(plyty[i][j][k] == '\n'){
                    x--;
                }
            }
            scanf("%c", &temp);
        }
        scanf("%c", &temp);
    }

    for (int i = 0; i < pow(4,k); i++)
    {
        for (int t = 0; t < k; t++)
        {
            if (i >= pow(4,t))
            {
                rotate(t,n);
            }
        }        
        sklej(n, k);
        int wynik = sprawdz(n);
        printf("|%d", wynik);
        for (int j = 0; j < n; j++)
        {
            for (int x = 0; x < n; x++)
            {
                printf("%c", sklejka[j][x]);
            }
            printf("\n");
        }
        printf("-------\n");
        while (getCHar)
        {
            /* code */
        }
        
    }

    

    // for (int i = 0; i < k; i++)
    // {
        // for (int j = 0; j < n; j++)
        // {
        //     for (int x = 0; x < n; x++)
        //     {
        //         printf("%c", sklejka[j][x]);
        //     }
        //     printf("\n");
        // }
        // printf("-------\n");
    // }
    

}