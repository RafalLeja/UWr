#include <stdio.h>
#include <string.h>

int main() {
    int n, k, max = 0, idx;
    idx = scanf("%d%d", &n, &k);
    char identyfikatory[n][k];

    for(int i = 0; i < n; i++){
        idx = scanf("%s", identyfikatory[i]);
    }

    idx = 0;

    for(int i = 0; i < n; i++){
        int unikatowosc = 0;

        for(int j = 0; j < k; j++){
            int count = 0;

            for(int l = 0; l < n; l++){
                if(identyfikatory[l][j] == identyfikatory[i][j]){
                    count++;
                }

                if(count > 1){
                    break;
                }
            }

            if(count == 1){
                unikatowosc++;
            }
        }

        if (unikatowosc > max){
            max = unikatowosc;
            idx = i;
        }
    }

    for(int i = 0; i < k; i++){
        printf("%c", identyfikatory[idx][i]);
    }
    printf("\n%d", max);

    return 0;
}