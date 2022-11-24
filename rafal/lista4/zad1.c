#include <stdio.h>

int F(int n){
    int x = n + 1;
    int i = 0;

    while (x != 1)
    {
        if (x % 2 == 0){
            x = x/2;
        }else if (x%2 == 1)
        {
            x = 3*x + 1;
        }
        i++;
    }
    return i;
}

void wykres(int maks, int N){
    char tab[maks+1][N];
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < maks+1; x++)
        {
            if (x == 0){
                tab[x][y] = '#';
            }else if (x <= F(y))
            {
                tab[x][y] = '#';
            }else if (x > F(y)){
                tab[x][y] = ' ';
            }
            
        }
        
    }
    
    for (int y = maks; y >= 0; y--)
    {
        for (int x = 0; x < N; x++)
        {
            printf("%c", tab[y][x]); 
        }
        printf("\n");
    }
    for (int i = 1; i < N; i*=10)
    {
        for (int j = 1; j < N+1; j++)
        {
            if (j%i == 0)
            {
                printf("%d", j/i%10);
            }else {
                printf(" ");
            }
        }
        printf("\n");
    }
    

}

int main()
{
    int N;
    scanf("%d", &N);
    int maks = 0;
    for (int i = 0; i < N; i++)
    {
        if (maks < F(i+1)){
            maks = F(i+1);
        }
    }
    wykres(maks, N);
    
    return 0;
}
