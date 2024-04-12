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
  unsigned char minIdx;
  unsigned char maxIdx;
};

struct out K(int F, int C, struct moneta *monety, struct out *wyniki){
  if (F == 0) return (struct out){0, 0, 0, 0};
  
  struct out wynik;
  wynik.min = 100000;
  wynik.max = 0;
  wynik.minIdx = 0;
  wynik.maxIdx = 0;

  for (int i = 0; i < C; i++){
    if (monety[i].weight <= F){
      struct out temp;
      if (wyniki[F-monety[i].weight].min != -1) {
        // printf("cached\n");
        temp = wyniki[F-monety[i].weight];
      } else {
        temp = K(F-monety[i].weight, C, monety, wyniki);
      }

      // if (F == 23){
      //   printf("F: %d, i: %d, temp.min: %d, temp.max: %d\n", F, i, temp.min, temp.max);
      // }

      // if (monety[i].val > 0 && monety[i].val > INT_MAX - temp.min)
      // {
      //   temp.min = INT_MAX;
      // }else{
        temp.min += monety[i].val;
      // }

      temp.max += monety[i].val;


      if (temp.max > wynik.max){
        wynik.max = temp.max;
        wynik.maxIdx = i;
      }

      if (temp.min < wynik.min){
        wynik.min = temp.min;
        wynik.minIdx = i;
      }

    }
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

  for (int i = 0; i < F; i++){
    wyniki[i] = (struct out){-1, -1, 0, 0};
  }
  wyniki[0] = (struct out){0, 0, 0, 0};

  int *minOut = (int*) calloc(C,sizeof(int));
  int *maxOut = (int*) calloc(C,sizeof(int));
  struct out wynik = K(F, C, monety, wyniki);
  
  // printf("-------\n");
  // for (int i = 0; i < F+1; i++){
  //   printf("%d: %d-%d %d-%d \n", i, wyniki[i].min, wyniki[i].minIdx, wyniki[i].max, wyniki[i].maxIdx);
  // }

  int tmpF = F;
  while (tmpF > 0){
    minOut[wyniki[tmpF].minIdx]++;
    tmpF -= monety[wyniki[tmpF].minIdx].weight;
  }

  tmpF = F;
  while (tmpF > 0){
    maxOut[wyniki[tmpF].maxIdx]++;
    tmpF -= monety[wyniki[tmpF].maxIdx].weight;
  }

  int sum1 = 0;
  int sum2 = 0;
  for (int i = 0; i < C; i++){
    sum1 += monety[i].weight * minOut[i];
    sum2 += monety[i].weight * maxOut[i];
  }
  if (sum1 != F || sum2 != F)
  {
    printf("NIE\n");
    return 0;
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



  free(monety);
  free(wyniki);
  free(minOut);
  free(maxOut);
}