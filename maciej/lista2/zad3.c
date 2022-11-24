#include<stdio.h>

int change = 1;


int east(int w, int h, char forest[h][w]){
    long cone = 0;
    for(int x = 0; x < h; x++){
        int y = w - 1;
        while(y >= 0){
            if(forest[x][y] == '9'){
                cone++;
                y -= (forest[x][y] - 47);
            }
            else if(forest[x][y] == '.'){
                y--;
            }
            else{
                forest[x][y]++;
                y -= (forest[x][y] - 48);
                change = 1;
            }
        }
    }
    return cone;
}

int south(int w, int h, char forest[h][w]){
    long cone = 0;
    for(int y = 0; y < w; y++){
        int x = h - 1;
        while(x >= 0){
            if(forest[x][y] == '9'){
                cone++;
                x -= (forest[x][y] - 47);
            }
            else if(forest[x][y] == '.'){
                x--;
            }
            else{
                forest[x][y]++;
                x -= (forest[x][y] - 48);
                change = 1;
            }
        }
    }
    return cone;
}

int west(int w, int h, char forest[h][w]){
    long cone = 0;
    for(int x = 0; x < h; x++){
        int y = 0;
        while(y < w){
            if(forest[x][y] == '9'){
                cone++;
                y += (forest[x][y] - 47);
            }
            else if(forest[x][y] == '.'){
                y++;
            }
            else{
                forest[x][y]++;
                y += (forest[x][y] - 48);
                change = 1;
            }
        }
    }
    return cone;
}

void print(int w, int h, char forest[h][w]){
    printf("\n\n");
    for(int x = 0; x < h; x++){
        for(int y = 0; y < w; y++){
            printf("%c", forest[x][y]);
        }
        printf("\n");
    }
}

int main(){
    int w, h;
    long days, cone = 0, per_day;
    scanf("%d%d%ld", &w, &h, &days);
    char forest[h][w];

    for(int x = 0; x < h; x++){
        for(int y = 0; y < w; y++){
            scanf(" %c", &forest[x][y]);
        }
    }

    while(days && change){
        change = 0;
        days--;
        per_day = cone;

        cone += east(w, h, forest);
        cone += south(w, h, forest);
        cone += west(w, h, forest);
        per_day = cone - per_day;
    }

    cone += per_day * days;

    printf("%ld", cone);
    return 0;
}