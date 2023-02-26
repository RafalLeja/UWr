#include<stdio.h>

typedef struct Pole{
    char znak;
    int dostep;
} pole;

int obroc(char s, int kierunek){
    if(s == 'L'){
        kierunek--;
        if(kierunek < 0){
            kierunek = 3;
        }
    }
    else{
        kierunek++;
        if(kierunek > 3){
            kierunek = 0;
        }
    }

    return kierunek;
}

int main(){
    int w, h, n, pom;
    pom = scanf("%d %d", &h, &w);
    pole mapa[w][h];
    char s;

    getchar();
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            mapa[x][y].znak = getchar();
        }
        getchar();
    }

    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            if(mapa[x][y].znak != '.'){
                mapa[x][y].dostep = 0;
            }
            else{
                int dostep = 1;
                if(x - 1 >= 0 && mapa[x - 1][y].znak == '.'){
                    dostep *= 2;
                }
                if(x + 1 < w && mapa[x + 1][y].znak == '.'){
                    dostep *= 5;
                }
                if(y - 1 >= 0 && mapa[x][y - 1].znak == '.'){
                    dostep *= 7;
                }
                if(y + 1 < h && mapa[x][y + 1].znak == '.'){
                    dostep *= 3;
                }
                mapa[x][y].dostep = dostep;
            }
        }
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
            if(mapa[x][y].dostep > 0){
                for(int k = 0; k < 4; k++){
                    int posX = x, posY = y;
                    int m = 0, kierunek = k;  //N - 0; E - 1; S - 2; W - 3;

                    while(m < n){
                        if(instrukcje[m] == 'L' || instrukcje[m] == 'R'){
                            kierunek = obroc(instrukcje[m], kierunek);
                        }

                        else if(kierunek == 2){
                            if(instrukcje[m] == 'F'){
                                while(posX + 1 < w && mapa[posX + 1][posY].dostep > 0){
                                    posX++;
                                }
                            }
                            else{
                                posX++;
                            }
                        }
                        
                        else if(kierunek == 1){
                            if(instrukcje[m] == 'F'){
                                while(posY + 1 < h && mapa[posX][posY + 1].dostep > 0){
                                    posY++;
                                }
                            }
                            else{
                                posY++;
                            }
                        }

                        else if(kierunek == 0){
                            if(instrukcje[m] == 'F'){
                                while(posX - 1 >= 0 && mapa[posX - 1][posY].dostep > 0){
                                    posX--;
                                }
                            }
                            else{
                                posX--;
                            }
                        }

                        else{
                            if(instrukcje[m] == 'F'){
                                while(posY - 1 >= 0 && mapa[posX][posY - 1].dostep > 0){
                                    posY--;
                                }
                            }
                            else{
                                posY--;
                            }
                        }
                        
                        if(posX < 0 || posY < 0 || posX >= w || posY >= h || mapa[posX][posY].dostep == 0){
                            break;
                        }
                    
                        m++;
                    }

                    if(m == n){
                        mapa[posX][posY].znak = 'X';
                    }
                }
            }
        }
    }


    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            printf("%c", mapa[x][y].znak);
        }
        printf("\n");
    }

    // for(int x = 0; x < w; x++){
    //     for(int y = 0; y < h; y++){
    //         printf(" %d ", mapa[x][y].dostep);
    //     }
    //     printf("\n");
    // }

    return 0;
}