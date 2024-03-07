// Rafał Leja
// 340879
// MBa

#include <stdio.h>
#include <stdlib.h>

void moveDown(int i, int n, unsigned int *Heap, unsigned int *Hierarchy);

int isParent(int a, int b, unsigned int *inTime, unsigned int *outTime);

void dfsTimes(int v, int t, unsigned int *inTime, unsigned int *outTime, unsigned int *hierarchy, int n);

int main(void)
{ 
  unsigned int n, q;
  scanf("%u %u", &n, &q);

  unsigned int *hierarchy;
  hierarchy = (unsigned int *)calloc((n-1), sizeof(unsigned int));

  unsigned int *inTime;
  inTime = (unsigned int *)calloc((n), sizeof(unsigned int));

  unsigned int *outTime;
  outTime = (unsigned int *)calloc((n), sizeof(unsigned int));

  for (int i = 0; i < n-1; i++) {
    scanf("%u", &hierarchy[i]);
  }

  dfsTimes(1, 1, inTime, outTime, hierarchy, n);

  // for (int i = 0; i < n; i++) {
  //   printf("K[%u] = %u, in: %u, out: %u\n", i+1, hierarchy[i-1], inTime[i], outTime[i]);
  // }

  for (int i = 0; i < q; i++) {
    unsigned int a, b;
    scanf("%u %u", &a, &b);
    if (isParent(a, b, inTime, outTime)) {
      printf("TAK\n");
    } else {
      printf("NIE\n");
    }
  }

  free(hierarchy);
  free(inTime);
  free(outTime);
  return 0;
}

void dfsTimes(int idx, int t, unsigned int *inTime, unsigned int *outTime, unsigned int *hierarchy, int n) {
  inTime[idx-1] = t;
  outTime[idx-1] = t;
  for (int i = 1; i <= n-1; i++) {
    inTime[i] = outTime[hierarchy[i-1]-1] + 1;
    outTime[i] = inTime[i];
    outTime[hierarchy[i-1]-1] += 1;
  }

  for (int i = n-1; i > 0; i--) {
    if (outTime[i] > outTime[hierarchy[i-1]-1]) {
      outTime[hierarchy[i-1]-1] = outTime[i];
    }
  }
}

int isParent(int a, int b, unsigned int *inTime, unsigned int *outTime){
  // printf("a in: %u, out: %u\n", inTime[a-1], outTime[a-1]);
  // printf("b in: %u, out: %u\n", inTime[b-1], outTime[b-1]);
  if (inTime[a-1] <= inTime[b-1] && outTime[a-1] >= outTime[b-1]) {
    return 1;
  } else {
    return 0;
  }
}