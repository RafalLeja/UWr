#include<stdio.h>

int main(){
    int x = 3;
    char tab[3][3] = {{'+','.','+'}, {'.', '.', '+'}, {'+', '.', '.'}};

    for(int m = 0; m < x; m++){         //0 stopni
        for(int n = 0; n < x; n++){
            printf("%c", tab[m][n]);
        }
        printf("\n");
    }

////////////////

    printf("\n");

    for(int m = x - 1; m >= 0; m--){         //90 stopni
        for(int n = 0; n < x; n++){
            printf("%c", tab[n][m]);
        }
        printf("\n");
    }

////////////////

printf("\n");

    for(int m = x - 1; m >= 0; m--){         //180 stopni
        for(int n = x - 1; n >= 0; n--){
            printf("%c", tab[n][m]);
        }
        printf("\n");
    }


////////////////

printf("\n");

    for(int m = 0; m < x; m++){         //270 stopni
        for(int n = x - 1; n >= 0; n--){
            printf("%c", tab[n][m]);
        }
        printf("\n");
    }


    return 0;
}