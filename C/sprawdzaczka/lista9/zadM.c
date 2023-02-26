#include<stdio.h>
#include<time.h>

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

    clock_t t;
    t = clock();

    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            if(mapa[x][y] == '.' || mapa[x][y] == 'X'){

                for(int k = 0; k < 4; k++){
                    int posX = x, posY = y;
                    int m = 0, kierunek = k;  //N - 0; E - 1; S - 2; W - 3;

                    while(m < n){
                        double time_taken = ((double)clock() - t)/CLOCKS_PER_SEC;
                        if(time_taken > 1.5){
                            break;
                        }

                        if(instrukcje[m] == 'L' || instrukcje[m] == 'R'){
                            kierunek = obroc(instrukcje[m], kierunek);
                        }

                        else if(kierunek == 2){
                            if(instrukcje[m] == 'F'){
                                while(posX + 1 < w && (mapa[posX + 1][posY] == '.' || mapa[posX + 1][posY] == 'X')){
                                    posX++;
                                }
                            }
                            else{
                                posX++;
                            }
                        }
                        
                        else if(kierunek == 1){
                            if(instrukcje[m] == 'F'){
                                while(posY + 1 < h && (mapa[posX][posY + 1] == '.' || mapa[posX][posY + 1] == 'X')){
                                    posY++;
                                }
                            }
                            else{
                                posY++;
                            }
                        }

                        else if(kierunek == 0){
                            if(instrukcje[m] == 'F'){
                                while(posX - 1 >= 0 && (mapa[posX - 1][posY] == '.' || mapa[posX - 1][posY] == 'X')){
                                    posX--;
                                }
                            }
                            else{
                                posX--;
                            }
                        }

                        else{
                            if(instrukcje[m] == 'F'){
                                while(posY - 1 >= 0 && (mapa[posX][posY - 1] == '.' || mapa[posX][posY - 1] == 'X')){
                                    posY--;
                                }
                            }
                            else{
                                posY--;
                            }
                        }
                        
                        if(posX < 0 || posY < 0 || posX >= w || posY >= h || (mapa[posX][posY] != '.' && mapa[posX][posY] != 'X')){
                            break;
                        }
                    
                        m++;
                    }

                    if(m == n){
                        mapa[posX][posY] = 'X';
                    }
                }
            }
        }
    }

    // for(int x = 0; x < n; x++){
    //     printf("%c", instrukcje[x]);
    // }
    // putchar('\n');

    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            printf("%c", mapa[x][y]);
        }
        printf("\n");
    }

    return 0;
}