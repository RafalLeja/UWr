#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct moneta {
  int val;
  int weight;
};

struct out {
  int min;
  int max;
};

struct out K(int F, int C, struct moneta *monety, int *minOut, int *maxOut, struct out *wyniki){
  if (F == 0) return (struct out){0, 0};
  
  struct out wynik;
  wynik.min = INT_MAX;
  wynik.max = 0;

  for (int i = 0; i < C; i++){
    if (monety[i].weight <= F){
      int *tempMinOut = (int*) calloc(C, sizeof(int));
      int *tempMaxOut = (int*) calloc(C, sizeof(int));
      struct out temp;
      if (wyniki[F-monety[i].weight].min != -1) {
        // printf("cached\n");
        temp.min = wyniki[F-monety[i].weight].min;
        temp.max = wyniki[F-monety[i].weight].max;
      } else {
        temp = K(F-monety[i].weight, C, monety, tempMinOut, tempMaxOut, wyniki);
      }

      temp.min += monety[i].val;
      temp.max += monety[i].val;

      // printf("F: %d, i: %d, temp.min: %d, temp.max: %d\n", F, i, temp.min, temp.max);

      if (temp.max > wynik.max){
        wynik.max = temp.max;
        for (int j = 0; j < C; j++){
          maxOut[j] = tempMaxOut[j];
          // printf("maxOut[%d]: %d\n", j, maxOut[j]);
        }
        maxOut[i]++;
      }

      if (temp.min < wynik.min){
        wynik.min = temp.min;
        for (int j = 0; j < C; j++){
          minOut[j] = tempMinOut[j];
        }
        minOut[i]++;
      }

      free(tempMinOut);
      free(tempMaxOut);
    }
  }

  int sumMin = 0;
  int sumMax = 0;
  for (int i = 0; i < C; i++){
    sumMin += monety[i].weight * minOut[i];
    sumMax += monety[i].weight * maxOut[i];
    // printf("minOut[%d]: %d, maxOut[%d]: %d\n", i, minOut[i], i, maxOut[i]);
  }
  if (sumMin != F)
  {
    wynik.min = INT_MAX;
  }
  if (sumMax != F)
  {
    wynik.max = 0;
  }

  wyniki[F] = wynik;
  
  return wynik;
}

int main(){
  int F;
  scanf("%d", &F);
  int C;
  scanf("%d", &C);

  struct moneta *monety = (struct moneta*) malloc(C*sizeof(struct moneta));
  for(int i = 0; i < C; i++){
    scanf("%d %d", &monety[i].val, &monety[i].weight);
  }

  struct out *wyniki = (struct out*) malloc((F+1)*sizeof(struct out));
  wyniki[0] = (struct out){0, 0};

  for (int i = 0; i < F; i++){
    wyniki[i] = (struct out){-1, -1};
  }

  int *minOut = (int*) calloc(C,sizeof(int));
  int *maxOut = (int*) calloc(C,sizeof(int));
  struct out wynik = K(F, C, monety, minOut, maxOut, wyniki);

  int sum = 0;
  for (int i = 0; i < C; i++){
    sum += monety[i].weight * minOut[i];
  }
  if (sum != F)
  {
    printf("NIE\n");
    // return 0;
  }
  
  printf("TAK\n");
  printf("%d\n", wynik.min);
  for (int i = 0; i < C; i++){
    printf("%d ", minOut[i]);
  }
  printf("\n");

  printf("%d\n", wynik.max);
  for (int i = 0; i < C; i++){
    printf("%d ", maxOut[i]);
  }
  printf("\n");

  printf("-------\n");
  for (int i = 0; i < F+1; i++){
    printf("%d: %d %d\n", i, wyniki[i].min, wyniki[i].max);
  }


  free(monety);
  free(minOut);
  free(maxOut);
}