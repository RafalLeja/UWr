#include <stdio.h>

void shift(int n, int *tab, int dir);

void hanoi(int n, int *A, int *B, int *C, int m);

void wyswietl(int n, int *A, int *B, int *C){
    while (getchar() != '\n');
    for (int i = 0; i < n; i++)
    {
        printf("%d|%d|%d\n", A[i], B[i], C[i]);
    }
    printf("\n");
}

int main(){
    int n;
    scanf("%d", &n);
    int A[n+1]; 
    int B[n+1];
    int C[n+1];
    for (int i = 0; i <= n; i++)
    {
        A[i] = n-i;
        B[i] = 0;
        C[i] = 0;
    }
    wyswietl(n, A,B,C);
    //shift(n+1, A, -1);
    hanoi(n, A, B, C, n);
    // for (int i = 0; i < n+1; i++)
    // {
    //     printf("%d | %d \n", A[i], i);
    // }
    
};

void shift(int n, int *tab, int dir){
    if (dir > 0)
    {
        for (int i = n; i > 0; i--)
        {
            tab[i-1] = tab[i-1-dir];
        }
        tab[0] = 0;
    }else
    {
        for (int i = 0; i <= n; i++)
        {
            tab[i] = tab[i+1];
        }
        tab[n-1] = 0;
    }
    
    
    
};

void hanoi(int n, int *A, int *B, int *C, int m){
    if (n < 1)
    {
        return;
    }
    
    hanoi(n - 1, A, C, B, m);
    wyswietl(m,A,B,C);
    //shift(n, B, 1);
    B[n-1] = A[n-1];
    A[n-1] = 0;
    //shift(n, A, -1);
    hanoi(n-1, C, B, A, m);
    wyswietl(m, A, B, C);
};