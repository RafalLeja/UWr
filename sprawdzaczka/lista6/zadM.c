#include<stdio.h>

int main(){
    int c, n;
    scanf("%d %d", &n, &c);
    char tab[c][n][n], s = getchar();

    for(int x = 0; x < c; x++){
        for(int y = 0; y < n; y++){
            for(int z = 0; z < n; z++){
                s = getchar();
                tab[x][y][z] = s;
            }
            s = getchar();
        }
        s = getchar();
    }

    for(int x = 0; x < c; x++){
        for(int y = 0; y < n; y++){
            for(int z = 0; z < n; z++){
                printf("%c", tab[x][y][z]);
            }
            printf("\n");
        }
        printf("\n");
    }



    return 0;
}