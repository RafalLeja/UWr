#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void K(int F, int C, int *wartosci, int *wagi, long long *wynikiMin, unsigned char *wynikiMinIdx, long long *wynikiMax, unsigned char *wynikiMaxIdx){

  long long wynikMin = LLONG_MAX;
  long long wynikMax = LLONG_MIN;
  unsigned char wynikMinIdx = 0;
  unsigned char wynikMaxIdx = 0;

  for (int i = 0; i < C; i++){
    if (wagi[i] <= F){
      if (wynikiMin[F-wagi[i]] == -1) {
        K(F-wagi[i], C, wartosci, wagi, wynikiMin, wynikiMinIdx, wynikiMax, wynikiMaxIdx);
      }

      long long tempMin = wynikiMin[F-wagi[i]];
      long long tempMax = wynikiMax[F-wagi[i]];


      if (tempMin != LLONG_MAX)
      {
        tempMin += wartosci[i];
      }
      
      if (tempMax != LLONG_MIN) {
        tempMax += wartosci[i];
      }

      if (tempMax > wynikMax){
        wynikMax = tempMax;
        wynikMaxIdx = i;
      }

      if (tempMin < wynikMin){
        wynikMin = tempMin;
        wynikMinIdx = i;
      }

    }
  }

  wynikiMin[F] = wynikMin;
  wynikiMax[F] = wynikMax;
  wynikiMinIdx[F] = wynikMinIdx;
  wynikiMaxIdx[F] = wynikMaxIdx;
}

int main(){
  int F;
  scanf("%d", &F);
  int C;
  scanf("%d", &C);

  int *wartosci = (int*) malloc(C*sizeof(int));
  int *wagi = (int*) malloc(C*sizeof(int));
  for(int i = 0; i < C; i++){
    scanf("%d %d", &wartosci[i], &wagi[i]);
  }

  long long *wynikiMin = (long long*) malloc((F+1)*sizeof(long long));
  unsigned char *wynikiMinIdx = (unsigned char*) malloc((F+1)*sizeof(unsigned char));
  long long *wynikiMax = (long long*) malloc((F+1)*sizeof(long long));
  unsigned char *wynikiMaxIdx = (unsigned char*) malloc((F+1)*sizeof(unsigned char));

  for (int i = 0; i < F; i++){
    wynikiMin[i] = -1;
    wynikiMax[i] = -1;
    wynikiMinIdx[i] = 0;
    wynikiMaxIdx[i] = 0;
  }
  wynikiMin[0] = 0;
  wynikiMax[0] = 0;
  wynikiMinIdx[0] = 0;
  wynikiMaxIdx[0] = 0;

  int *minOut = (int*) calloc(C,sizeof(int));
  int *maxOut = (int*) calloc(C,sizeof(int));
  
  K(F, C, wartosci, wagi, wynikiMin, wynikiMinIdx, wynikiMax, wynikiMaxIdx);
  
  int wynikMin = wynikiMin[F];
  int wynikMax = wynikiMax[F];
  
  // printf("-------\n");
  // for (int i = 0; i < F+1; i++){
  //   printf("%d: %d-%d %d-%d \n", i, wyniki[i].min, wyniki[i].minIdx, wyniki[i].max, wyniki[i].maxIdx);
  // }

  int tmpF = F;
  while (tmpF > 0){
    minOut[wynikiMinIdx[tmpF]]++;
    tmpF -= wagi[wynikiMinIdx[tmpF]];
  }

  tmpF = F;
  while (tmpF > 0){
    maxOut[wynikiMaxIdx[tmpF]]++;
    tmpF -= wagi[wynikiMaxIdx[tmpF]];
  }

  int sum1 = 0;
  int sum2 = 0;
  for (int i = 0; i < C; i++){
    sum1 += wagi[i] * minOut[i];
    sum2 += wagi[i] * maxOut[i];
  }
  if (sum1 != F || sum2 != F)
  {
    printf("NIE\n");
    return 0;
  }

  
  printf("TAK\n");
  printf("%d\n", wynikMin);
  for (int i = 0; i < C; i++){
    printf("%d ", minOut[i]);
  }
  printf("\n");

  printf("%d\n", wynikMax);
  for (int i = 0; i < C; i++){
    printf("%d ", maxOut[i]);
  }
  printf("\n");



  free(wartosci);
  free(wagi);
  free(wynikiMin);
  free(wynikiMax);
  free(wynikiMinIdx);
  free(wynikiMaxIdx);
  free(minOut);
  free(maxOut);
}