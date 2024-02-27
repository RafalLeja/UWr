// Rafał Leja
// 340879
// MBa

#include <stdio.h>

void buildHeap(int n, unsigned short *Heap, unsigned short *Hierarchy);

void moveDown(int i, int n, unsigned short *Heap, unsigned short *Hierarchy);

int main(void)
{ 
  unsigned short n, q;
  scanf("%hu %hu", &n, &q);
  unsigned short desc[n-1];
  for (int i = 0; i < n-1; i++) {
    scanf("%hu", &desc[i]);
  }

  unsigned short heap[n];
  for (int i = 0; i < n; i++) {
    heap[i] = i+1;
  }
 
  buildHeap(n, heap, desc);

  // printf("n = %hu, q = %hu\n", n, q);
  for (int i = 0; i < n; i++) {
    printf("K[%d] = %hu\n", i, heap[i]);
  }

  // for (int i = 0; i < n-1; i++) {
    // printf("desc[%d] = %hu\n", i, desc[i]);
  // }

  // printf("size = %ld", sizeof(desc));

  return 0;
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
}
