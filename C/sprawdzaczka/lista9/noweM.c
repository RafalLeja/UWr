#include<stdio.h>

int obroc(char s, int kierunek){
    if(s == 'L'){
        kierunek++;
        if(kierunek > 3){
            kierunek = 0;
        }
    }
    else{
        kierunek--;
        if(kierunek < 0){
            kierunek = 3;
        }
    }

    return kierunek;
}

int main(){
    int w, h, n, pom;
    pom = scanf("%d %d", &h, &w);
    char mapa[w][h], s;

    getchar();
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            mapa[x][y] = getchar();
        }
        getchar();
    }

    pom = scanf("%d", &n);
    char instrukcje[n];
    pom = 0;
    while(pom < n){
        if((s = getchar()) != '\n'){
            instrukcje[pom] = s;
            pom++;
        }
    }

    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            if(mapa[x][y] == '.'){
                for(int k = 0; k < 4; k++){
                    if(mapa[x][y] == 'X'){
                        break;
                    }

                    int posX = x, posY = y;
                    int m = n - 1, kierunek = k;  //N - 0; E - 1; S - 2; W - 3
                    while(m >= 0){
                        if(instrukcje[m] == 'L' || instrukcje[m] == 'R'){
                            kierunek = obroc(instrukcje[m], kierunek);
                        }

                        else if(instrukcje[m] == 'F'){
                            if(kierunek == 0){
                                if(posX - 1 < 0 || (mapa[posX - 1][posY] != '.' && mapa[posX - 1][posY] != 'X')){
                                    while(posX + 1 < w && (mapa[posX + 1][posY] == '.' || mapa[posX + 1][posY] == 'X')){
                                        posX++;
                                    }
                                }
                                else{
                                    break;
                                }
                            }
                            else if(kierunek == 1){
                                if(posY + 1 >= h || (mapa[posX][posY + 1] != '.' && mapa[posX][posY + 1] != 'X')){
                                    while(posY - 1 >= 0 && (mapa[posX][posY - 1] == '.' || mapa[posX][posY - 1] == 'X')){
                                        posY--;
                                    }
                                }
                                else{
                                    break;
                                }
                            }
                            else if(kierunek == 2){
                                if(posX + 1 >= w || (mapa[posX + 1][posY] != '.' && mapa[posX + 1][posY] != 'X')){
                                    while(posX - 1 >= 0 && (mapa[posX - 1][posY] == '.' || mapa[posX - 1][posY] == 'X')){
                                        posX--;
                                    }
                                }
                                else{
                                    break;
                                }
                            }
                            else{
                                if(posY - 1 < 0 || (mapa[posX][posY - 1] != '.' && mapa[posX][posY - 1] != 'X')){
                                    while(posY + 1 < h && (mapa[posX][posY + 1] == '.' || mapa[posX][posY + 1] == 'X')){
                                        posY++;
                                    }
                                }
                                else{
                                    break;
                                }
                            }
                        }

                        else{
                            if(kierunek == 0){
                                if(posX + 1 >= w || (mapa[posX + 1][posY] != '.' && mapa[posX + 1][posY] != 'X')){
                                    break;
                                }
                                else{
                                    posX++;
                                }
                            }
                            
                            else if(kierunek == 1){
                                if(posY - 1 < 0 || (mapa[posX][posY - 1] != '.' && mapa[posX][posY - 1] != 'X')){
                                    break;
                                }
                                else{
                                    posY--;
                                }
                            }
                            
                            else if(kierunek ==2){
                                if(posX - 1 < 0 || (mapa[posX - 1][posY] != '.' && mapa[posX - 1][posY] != 'X')){
                                    break;
                                }
                                else{
                                    posX--;
                                }
                            }

                            else{
                                if(posY + 1 >= h || (mapa[posX][posY + 1] != '.' && mapa[posX][posY + 1] != 'X')){
                                    break;
                                }
                                else{
                                    posY++;
                                }
                            }
                        }
                        m--;
                    }
                    if(m < 0){
                        mapa[x][y] = 'X';
                    }
                }
            }
        }
    }

    for(int x = 0; x < w; x++){
            for(int y = 0; y < h; y++){
                printf("%c", mapa[x][y]);
            }
            printf("\n");
        }

    return 0;
}