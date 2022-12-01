#include <stdio.h>

void rotate(char **tab, int n){
    char temp[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp[i][j] = tab[i][j];
        }
        
    }
        for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            tab[j][i] = temp[i][j];
        }
        
    }
    
}

int main(){
    // int n, k;
    // scanf("%d %d", &n, &k);
    // char tab[k][n][n];
    // char temp;
    // scanf("%c", &temp);
    // for (int i = 0; i < k; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         for (int x = 0; x < n; x++)
    //         {
    //             scanf("%c", &tab[i][j][x]);
    //             if(tab[i][j][k] == '\n'){
    //                 x--;
    //             }
    //         }
    //         scanf("%c", &temp);
    //     }
    //     scanf("%c", &temp);
    // }

    // for (int i = 0; i < 4; i++)
    // {
    //     /* code */
    // }
    // for (int i = 0; i < k; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         for (int k = 0; k < n; k++)
    //         {
    //             printf("%c", tab[i][j][k]);
    //         }
    //         printf("\n");
    //     }
    //     printf("----\n");
    // }
    
    char tab[2][2] = {{'a','a'}, {'b', 'b'}};
    for (int i = 0; i < 2; i++)
    {
        for (int k = 0; k < 2; k++)
        {
            printf("%c", tab[i][k]);
        }
        printf("\n");
    }
    rotate(&tab, 2);
        for (int i = 0; i < 2; i++)
    {
        for (int k = 0; k < 2; k++)
        {
            printf("%c", tab[i][k]);
        }
        printf("\n");
    }
}