#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct moneta {
  int val;
  int weight;
};

int Kmax(int F, int C, struct moneta *monety, int* wyniki){
  if (F == 0) return 0;
  int max = 0;

  for (int i = 0; i < C; i++){
    if (monety[i].weight <= F){
      int temp;
      if (wyniki[F-monety[i].weight] != -1) {
        temp = wyniki[F-monety[i].weight] + monety[i].val;
      }
      temp = Kmax(F-monety[i].weight, C, monety, wyniki) + monety[i].val;

      if (temp > max){
        max = temp;
      }
    }
  }

  wyniki[F] = max;

  return max;
}

int Kmin(int F, int C, struct moneta *monety, int* wyniki){
  if (F == 0) return 0;
  int min = INT_MAX;

  for (int i = 0; i < C; i++){
    if (monety[i].weight <= F){
      int temp;
      if (wyniki[F-monety[i].weight] != -1) {
        temp = wyniki[F-monety[i].weight] + monety[i].val;
      }
      temp = Kmin(F-monety[i].weight, C, monety, wyniki) + monety[i].val;

      if (temp < min){
        min = temp;
      }
    }
  }

  wyniki[F] = min;

  return min;
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

  int *wynikiMin = (int*) calloc((F+1), sizeof(int));
  int min = Kmin(F, C, monety, wynikiMin);

  for (int i = 0; i < F+1; i++){
    printf("wynikiMin[%d] = %d\n", i, wynikiMin[i]);
  }
  printf("\n");

  // int sum = 0;
  // for (int i = 0; i < C; i++){
  //   sum += monety[i].weight * minOut[i];
  // }
  // if (sum != F)
  // {
  //   printf("NIE\n");
  //   return 0;
  // }
  
  // printf("TAK\n");
  printf("%d\n", min);
  // for (int i = 0; i < C; i++){
  //   printf("%d ", minOut[i]);
  // }
  // printf("\n");

  int *wynikiMax = (int*) malloc((F+1)*sizeof(int));
  int max = Kmax(F, C, monety, wynikiMax);
  printf("%d\n", max);
  // for (int i = 0; i < C; i++){
  //   printf("%d ", maxOut[i]);
  // }
  // printf("\n");


  free(monety);
  // free(minOut);
  // free(maxOut);
}