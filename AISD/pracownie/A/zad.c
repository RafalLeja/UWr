// Rafał Leja
// 340879
// MBa

#include <stdio.h>
#include <stdlib.h>

void buildHeap(int n, unsigned int *Heap, unsigned int *Hierarchy);

void moveDown(int i, int n, unsigned int *Heap, unsigned int *Hierarchy);

int isParent(int a, int b, unsigned int *inTime, unsigned int *outTime, unsigned int *heap);

void dfsTimes(int v, int t, unsigned int *inTime, unsigned int *outTime, unsigned int *heap, int n);

int main(void)
{ 
  unsigned int n, q;
  scanf("%u %u", &n, &q);

  unsigned int *hierarchy;
  hierarchy = (unsigned int *)calloc((n-1), sizeof(unsigned int));

  unsigned int *heap;
  heap = (unsigned int *)calloc((n), sizeof(unsigned int));

  unsigned int *inTime;
  inTime = (unsigned int *)calloc((n), sizeof(unsigned int));

  unsigned int *outTime;
  outTime = (unsigned int *)calloc((n), sizeof(unsigned int));

  for (int i = 0; i < n-1; i++) {
    scanf("%u", &hierarchy[i]);
  }

  for (int i = 0; i < n; i++) {
    heap[i] = i+1;
  }

  buildHeap(n, heap, hierarchy);

  dfsTimes(1, 1, inTime, outTime, heap, n);

  for (int i = 0; i < n; i++) {
    printf("K[%u] = %u, in: %u, out: %u\n", i+1, heap[i], inTime[i], outTime[i]);
  }

  for (int i = 0; i < q; i++) {
    unsigned int a, b;
    scanf("%u %u", &a, &b);
    if (isParent(a, b, inTime, outTime, heap)) {
      printf("TAK\n");
    } else {
      printf("NIE\n");
    }
  }

  free(hierarchy);
  return 0;
}

void dfsTimes(int idx, int t, unsigned int *inTime, unsigned int *outTime, unsigned int *heap, int n) {
  inTime[heap[idx-1]-1] = t;
  outTime[heap[idx-1]-1] = t;
  if (2*idx <= n) {
    dfsTimes(2*idx, t+1, inTime, outTime, heap, n);
    outTime[heap[idx-1]-1] = outTime[heap[2*idx-1]-1];
  }
  if (2*idx+1 <= n) {
    dfsTimes(2*idx+1, outTime[heap[idx-1]-1]+1, inTime, outTime, heap, n);
    outTime[heap[idx-1]-1] = outTime[heap[2*idx]-1];
  }
}

int isParent(int a, int b, unsigned int *inTime, unsigned int *outTime, unsigned int *heap){
  printf("a in: %u, out: %u\n", inTime[a-1], outTime[a-1]);
  printf("b in: %u, out: %u\n", inTime[b-1], outTime[b-1]);
  if (inTime[a-1] <= inTime[b-1] && outTime[a-1] >= outTime[b-1]) {
    return 1;
  } else {
    return 0;
  }
}

void buildHeap(int n, unsigned int *Heap, unsigned int *Hierarchy){
  for (int i = n/2 + n%2; i > 0; i--) {
    moveDown(i, n , Heap, Hierarchy);
  }
}

void moveDown(int i, int n, unsigned int *Heap, unsigned int *Hierarchy){
  int j = 0;
  while (i!=j) {
    j = i;
    if (2*j <= n && Hierarchy[2*j] > Hierarchy[i]) i = 2*j;
    if (2*j < n && Hierarchy[2*j+1] > Hierarchy[i]) i = 2*j+1;
    unsigned int temp = Heap[j];
    Heap[j] = Heap[i];
    Heap[i] = temp;
  }
}