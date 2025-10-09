/*
 * Rafał Leja 340879
 * MIA 2025
 * Zadanie B, Lista 1
 * 07.10.2025
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int testy;
  scanf("%d", &testy);

  for (int test = 0; test < testy; test++) {
    int len;
    scanf("%d", &len);

    int *arr = calloc(len, sizeof(int));
    for (int i = 0; i < len; i++) {
      scanf("%d", &arr[i]);
    }

    /*
     * dp[i] = najlepszy wynik do i-tego miejsca
     */
    int *dp = calloc(len, sizeof(int));
    /*
     * start[i][j] = j-te wystąpienie cyfry i
     */
    int **start = calloc(len, sizeof(int *));
    /*
     * ilosc[i] = ilosc cyfr i do tej pory
     */
    int *ilosc = calloc(len, sizeof(int));

    if (arr[0] == 1) {
      dp[0] = 1;
    }
    ilosc[arr[0]] = 1;
    start[arr[0]][0] = 0;

    for (int i = 1; i < len; i++) {
      int bierz = 0;
      if (ilosc[arr[i]] == arr[i] - 1) {
        int poprzednie = start[arr[i]][ilosc[arr[i]]] > 0
                             ? dp[start[arr[i]][ilosc[arr[i]]] - 1]
                             : 0;
        bierz = arr[i] + poprzednie;
      }

      int zostaw = dp[i - 1];

      dp[i] = bierz > zostaw ? bierz : zostaw;

      start[arr[i]][ilosc[arr[i]]] = i;
      ilosc[arr[i]]++;
    }

    printf("%d", dp[len - 1]);
  }
  return EXIT_SUCCESS;
}
