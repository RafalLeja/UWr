#include<stdio.h>

char dodatkowa[1][1];

int licz(int n){
    int licznik = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(dodatkowa[i][j] == '#'){
                licznik++;
            }
            dodatkowa[i][j] = '0';
        }
    }
    return licznik;
}

int main(){
    int c, n;
    scanf("%d %d", &n, &c);
    char tab[c][n][n], s = getchar();
    char dodatkowa[n][n];
    int dziury[n*n + 1];

///wypelnienie tablicy ilosci dziur zerami
    for(int i = 0; i < n * n + 1; i++){
        dziury[i] = 0;
    }
///

///wczytanie danych
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
///

    for(int i = 0; i < c; i++){
        for(int k = 0; k < n; k++){
            for(int l = 0; l < n; l++){
                if(dodatkowa[k][l] != '.'){
                    dodatkowa[k][l] = tab[i][k][l];
                }
            }
        }
    }

    for(int k = 0; k < n; k++){
        for(int l = 0; l < n; l++){
            printf("%c", dodatkowa[k][l]);
        }
        printf("\n");
    }


    dziury[licz(n)]++;

///sprawdzenie mozliwych ilosc dziur
    for(int i = 0; i < n * n + 1; i++){
        if(dziury[i] > 0){
            printf("%d ", i);
        }
    }
///

    return 0;
}