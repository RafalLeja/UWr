#include <stdio.h>
#include <math.h>

// char obrocona[15][20][20];
char plyty[15][20][20];
char sklejka[20][20];
int wyniki[20*20];

void rotate(int id, int n){
    char temp;
    for (int i = 0; i < n / 2; i++)
    {
    for (int j = i; j < n - i - 1; j++)
    {
        temp = plyty[id][i][j];
        plyty[id][i][j] = plyty[id][j][n-1-i];
        plyty[id][j][n-1-i] = plyty[id][n-1-i][n-1-j];
        plyty[id][n-1-i][n-1-j] = plyty[id][n-1-j][i];
        plyty[id][n-1-j][i] = temp;
       }
    }
}

void sklej(int n, int k){
    int sciana = 0;
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {
            for (int id = k-1; id >= 0; id--)
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
    int zda;
    zda = scanf("%d %d", &n, &k);
    char temp;
    zda = scanf("%c", &temp);
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int x = 0; x < n; x++)
            {
                zda = scanf("%c", &plyty[i][j][x]);
                if(plyty[i][j][k] == '\n'){
                    x--;
                }
            }
            zda = scanf("%c", &temp);
        }
        zda = scanf("%c", &temp);
    }
    zda += 1;
    
    // sklej(n,k);
    // for (int i = 0; i < k; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         for (int x = 0; x < n; x++)
    //         {
    //             printf("%c", plyty[i][j][x]);
    //         }
    //         printf("\n");
    //     }
    //     printf("-------\n");
    // }
    // for (int j = 0; j < n; j++)
    //     {
    //         for (int x = 0; x < n; x++)
    //         {
    //             printf("%c", sklejka[j][x]);
    //         }
    //         printf("\n");
    //     }
    // return 0;

    for (int i = 0; i < pow(4,k-1); i++)
    {
        for (int t = 0; t < k; t++)
        {
            int q = pow(4,t);
            if (i % q < pow(4,t-1))
            {
                rotate(t,n);
            }
        }        
        sklej(n, k);
        int wynik = sprawdz(n);
        // printf("|%d\n", wynik);
        // for (int j = 0; j < n; j++)
        // {
        //     for (int x = 0; x < n; x++)
        //     {
        //         printf("%c", sklejka[x][j]);
        //     }
        //     printf("\n");
        // }
        for (int i = 0; i < n*n; i++)
        {
            if (i == wynik)
            {
                wyniki[i]++;
            }
            
        }
        
        //printf("-------\n");

        
    }

    
    for (int i = 0; i < n*n; i++)
    {
        if (wyniki[i] > 0)
        {
            printf("%d ", i);
        }
        
    }
    
    

}