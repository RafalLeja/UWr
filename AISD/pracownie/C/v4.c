#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct moneta {
  int val;
  int weight;
  float ratio;
  char index;
};

int compareR(const void *a, const void *b){
  struct moneta *m1 = (struct moneta*)a;
  struct moneta *m2 = (struct moneta*)b;
  if (m1->ratio > m2->ratio) return -1;
  if (m1->ratio < m2->ratio) return 1;
  if (m1->weight > m2->weight) return -1;
  if (m1->weight < m2->weight) return 1;
  return 0;
}

int main(){
  int F;
  scanf("%d", &F);
  int C;
  scanf("%d", &C);

  struct moneta *monety = (struct moneta*) malloc(C*sizeof(struct moneta));
  for(int i = 0; i < C; i++){
    scanf("%d %d", &monety[i].val, &monety[i].weight);
    monety[i].ratio = (float)monety[i].val / monety[i].weight;
    monety[i].index = i;
  }


  qsort(monety, C, sizeof(char), compareR);

  // for (int i = 0; i < C; i++){
  //   printf("%d %d %f %d\n", monety[i].val, monety[i].weight, monety[i].ratio, monety[i].index);
  // }

  int *iloscMax = (int*) calloc(C, sizeof(int));
  // printf("calloc %d\n", C*sizeof(int));
  int *iloscMin = (int*) calloc(C, sizeof(int));
  int wynikMax = 0;
  int wynikMin = 0;
  
  int tmpF = F;
  for (int i = 0; i < C; i++){
    if (tmpF >= monety[i].weight){
      iloscMax[monety[i].index] = tmpF / monety[i].weight;
      tmpF -= iloscMax[monety[i].index] * monety[i].weight;
      wynikMax += iloscMax[monety[i].index] * monety[i].val;
    }
  }

  if (tmpF > 0){
    printf("NIE");
    return 0;
  }

  tmpF = F;
  for (int i = C-1; i >= 0; i--){
    if (tmpF >= monety[i].weight){
      iloscMin[monety[i].index] = tmpF / monety[i].weight;
      tmpF -= iloscMin[monety[i].index] * monety[i].weight;
      wynikMin += iloscMin[monety[i].index] * monety[i].val;
    }
  }

  if (tmpF > 0){
    printf("NIE");
    return 0;
  }
  printf("TAK\n");

  printf("%d\n", wynikMin);
  for (int i = 0; i < C; i++){
    printf("%d ", iloscMin[i]);
  }
  printf("\n");

  printf("%d\n", wynikMax);
  for (int i = 0; i < C; i++){
    printf("%d ", iloscMax[i]);
  }
  

  free(monety);
  free(iloscMax);
  free(iloscMin);

}