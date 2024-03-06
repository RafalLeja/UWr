// Rafał Leja
// 340879
// MBa

#include <stdio.h>
#include <stdlib.h>

void buildHeap(int n, unsigned short *Heap, unsigned short *Hierarchy);

void moveDown(int i, int n, unsigned short *Heap, unsigned short *Hierarchy);

int isParent(int a, int b, unsigned short *hierarchy);

int main(void)
{ 
  unsigned short n, q;
  scanf("%hu %hu", &n, &q);

  unsigned short *hierarchy;
  hierarchy = (unsigned short *)calloc((n-1), sizeof(unsigned short));

  for (int i = 0; i < n-1; i++) {
    scanf("%hu", &hierarchy[i]);
  }

  for (int i = 0; i < q; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    if (isParent(a, b, hierarchy)) {
      printf("TAK\n");
    } else {
      printf("NIE\n");
    }
  }

  free(hierarchy);
  return 0;
}

int isParent(int a, int b, unsigned short *hierarchy){
  if (a == 1) return 1;
  while (b != 1 && b != a) {
    b = hierarchy[b-2];
  }
  return b == a;
}

void buildHeap(int n, unsigned short *Heap, unsigned short *Hierarchy){
  for (int i = n/2 + n%2; i > 0; i--) {
    printf("i = %d\n", i);
    moveDown(i, n , Heap, Hierarchy);
  }
}

void moveDown(int i, int n, unsigned short *Heap, unsigned short *Hierarchy){
  int j = 0;
  while (i!=j) {
    j = i;
    if (2*j <= n && Hierarchy[2*j] > Hierarchy[i]) i = 2*j;
    if (2*j < n && Hierarchy[2*j+1] > Hierarchy[i]) i = 2*j+1;
    unsigned short temp = Heap[j];
    Heap[j] = Heap[i];
    Heap[i] = temp;
  }