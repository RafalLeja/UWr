#include <stdio.h>
#include <string.h>

int main() {
    int n, k, max = 0, idx;
    idx = scanf("%d%d", &n, &k);
    char id[n][k];

    for(int i = 0; i < n; i++){
        idx = scanf("%s", id[i]);
    }

    idx = 0;

    for(int i = 0; i < n; i++){
        int u = 0;

        for(int j = 0; j < k; j++){
            int c = 0;

            for(int l = 0; l < n; l++){
                if(id[l][j] == id[i][j]){
                    c++;
                }

                if(c > 1){
                    break;
                }
            }

            if(c == 1){
                u++;
            }
        }

        if (u > max){
            max = u;
            idx = i;
        }
    }

    for(int i = 0; i < k; i++){
        printf("%c", id[idx][i]);
    }
    printf("\n%d", max);

    return 0;
}