#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct moneta {
  int val;
  int weight;
};

int Kmax(int F, int C, struct moneta *monety, int *out){
  if (F == 0) return 0;
  int max = 0;

  for (int i = 0; i < C; i++){
    if (monety[i].weight <= F){
      int *tempOut = (int*) malloc(C*sizeof(int));
      int temp = Kmax(F-monety[i].weight, C, monety, tempOut) + monety[i].val;

      if (temp > max){
        max = temp;
        for (int j = 0; j < C; j++){
          out[j] = tempOut[j];
        }
        out[i]++;
      }
      free(tempOut);
    }
  }

  return max;
}

int Kmin(int F, int C, struct moneta *monety, int *out){
  if (F == 0) return 0;
  int min = INT_MAX;

  for (int i = 0; i < C; i++){
    if (monety[i].weight <= F){
      int *tempOut = (int*) calloc(C, sizeof(int));
      int temp = Kmin(F-monety[i].weight, C, monety, tempOut) + monety[i].val;
      if (temp < min){
        min = temp;
        for (int j = 0; j < C; j++){
          out[j] = tempOut[j];
        }
        out[i]++;
      }
      free(tempOut);
    }
  }

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

  int *minOut = (int*) malloc(C*sizeof(int));
  int min = Kmin(F, C, monety, minOut);

  int sum = 0;
  for (int i = 0; i < C; i++){
    sum += monety[i].weight * minOut[i];
  }
  if (sum != F)
  {
    printf("NIE\n");
    return 0;
  }
  
  printf("TAK\n");
  printf("%d\n", min);
  for (int i = 0; i < C; i++){
    printf("%d ", minOut[i]);
  }
  printf("\n");

  int *maxOut = (int*) malloc(C*sizeof(int));
  int max = Kmax(F, C, monety, maxOut);
  printf("%d\n", max);
  for (int i = 0; i < C; i++){
    printf("%d ", maxOut[i]);
  }
  printf("\n");


  free(monety);
  free(minOut);
  free(maxOut);
}