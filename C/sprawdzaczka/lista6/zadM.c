#include<stdio.h>

int licz(int n, char dodatkowa[][n]){
    int licznik = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(dodatkowa[i][j] == '.'){
                licznik++;
            }
            dodatkowa[i][j] = '0';
        }
    }
    return licznik;
}

void sklejPizde(int n, char tab[][n], char dodatkowa[][n]){
    for(int k = 0; k < n; k++){
        for(int l = 0; l < n; l++){
            if(dodatkowa[k][l] != '#'){
                dodatkowa[k][l] = tab[k][l];
            }
        }
    }
}

void rotate(int n, char tab[][n]){
    char temp[n][n];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            temp[i][j] = tab[i][j];
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            tab[j][i] = temp[i][j];
        }
    }
}

int main(){
    int c, n;
    scanf("%d %d", &n, &c);
    char tab[c][n][n], s = getchar();
    char dodatkowa[n][n];
    int dziury[n*n + 1];

///wypelnienie tablicy dziury zerami
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



    int i = 0;
    
    while(i < c){
        for(int j = 0; j < c; j++){
            sklejPizde(n, tab[i], dodatkowa);
        }
        dziury[licz(n, dodatkowa)];

        rotate(n, tab[i]);
        for(int j = 0; j < c; j++){
            sklejPizde(n, tab[i], dodatkowa);
        }

        dziury[licz(n, dodatkowa)];


        i++;
    }


//wypisanie mozliwych ilosc dziur
    for(int i = 0; i < n * n + 1; i++){
        if(dziury[i] > 0){
            printf("%d ", i);
        }
    }
//

    return 0;
}