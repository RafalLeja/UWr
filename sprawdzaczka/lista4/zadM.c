#include<stdio.h>

int main(){
    int n, row = 0, snake = 0, poprzedni = 0, diagonal = 0, dlugosc = 0;
    scanf("%d", &n);
    int tab[n][n];

    for(int i = 0; i < n; i++){     //wczytywanie danych
        for(int j = 0; j < n; j++){
            scanf("%d", &tab[i][j]);
        }
    }

//row
    poprzedni = tab[0][0];
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j++){
            if(tab[i][j] && poprzedni){
                dlugosc++;
            }
            else if(tab[i][j]){
                dlugosc = 1;
            }
            else if(dlugosc > row){
                row = dlugosc;
            }
            poprzedni = tab[i][j];
        }
    }

    if(dlugosc > row){
        row = dlugosc;
    }

//snake
    poprzedni = tab[0][0];
    dlugosc = 0;
    for(int i = 0; i < n; i++){
        if(i % 2 == 0){
            for(int j = 0; j < n; j++){     //lewa -> prawa
                if(tab[i][j] && poprzedni){
                    dlugosc++;
                }
                else if(tab[i][j]){
                    dlugosc = 1;
                }
                else if(dlugosc > row){
                    snake = dlugosc;
                }
                poprzedni = tab[i][j];
            }
        }
        else{
            for(int j = n - 1; j >= 0; j--){    //lewa <- prawa
                if(tab[i][j] && poprzedni){
                    dlugosc++;
                }
                else if(tab[i][j]){
                    dlugosc = 1;
                }
                else if(dlugosc > row){
                    snake = dlugosc;
                }
                poprzedni = tab[i][j];
            }
        }
    }
    if(dlugosc > snake){
        snake = dlugosc;
    }

//diagonal
    poprzedni = tab[0][0];
    dlugosc = 0;
    int i = 0, j = 0;
        if(tab[i][j] && poprzedni){
        dlugosc++;
    }
    else if(tab[i][j]){
        dlugosc = 1;
    }
    else if(dlugosc > row){
        diagonal = dlugosc;
    }
    poprzedni = tab[i][j];
    while(i < n - 1 || j < n - 1){
        if(j < n - 1){
            j++;
                if(tab[i][j] && poprzedni){
        dlugosc++;
    }
    else if(tab[i][j]){
        dlugosc = 1;
    }
    else if(dlugosc > row){
        diagonal = dlugosc;
    }
    poprzedni = tab[i][j];
            while(j > 0){
                i++;
                j--;
                    if(tab[i][j] && poprzedni){
        dlugosc++;
    }
    else if(tab[i][j]){
        dlugosc = 1;
    }
    else if(dlugosc > row){
        diagonal = dlugosc;
    }
    poprzedni = tab[i][j];
            }
        }
        else{
            i++;
                if(tab[i][j] && poprzedni){
        dlugosc++;
    }
    else if(tab[i][j]){
        dlugosc = 1;
    }
    else if(dlugosc > row){
        diagonal = dlugosc;
    }
    poprzedni = tab[i][j];
            while(i < n - 1){
                i++;
                j--;
                    if(tab[i][j] && poprzedni){
        dlugosc++;
    }
    else if(tab[i][j]){
        dlugosc = 1;
    }
    else if(dlugosc > row){
        diagonal = dlugosc;
    }
    poprzedni = tab[i][j];
            }
        }
    
        if(i < n - 1){
            i++;
                if(tab[i][j] && poprzedni){
        dlugosc++;
    }
    else if(tab[i][j]){
        dlugosc = 1;
    }
    else if(dlugosc > row){
        diagonal = dlugosc;
    }
    poprzedni = tab[i][j];
            while(i > 0){
                j++;
                i--;
                    if(tab[i][j] && poprzedni){
        dlugosc++;
    }
    else if(tab[i][j]){
        dlugosc = 1;
    }
    else if(dlugosc > row){
        diagonal = dlugosc;
    }
    poprzedni = tab[i][j];
            }
        }
        else{
            j++;
                if(tab[i][j] && poprzedni){
        dlugosc++;
    }
    else if(tab[i][j]){
        dlugosc = 1;
    }
    else if(dlugosc > row){
        diagonal = dlugosc;
    }
    poprzedni = tab[i][j];
            while(j < n - 1){
                j++;
                i--;
                    if(tab[i][j] && poprzedni){
        dlugosc++;
    }
    else if(tab[i][j]){
        dlugosc = 1;
    }
    else if(dlugosc > row){
        diagonal = dlugosc;
    }
    poprzedni = tab[i][j];
            }
        }
    }
    if(dlugosc > diagonal){
        diagonal = dlugosc;
    }

    printf("%d %d %d", row, snake, diagonal);

    return 0;
}