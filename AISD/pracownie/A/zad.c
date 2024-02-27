// Rafał Leja
// 340879
// MBa

#include <stdio.h>

void buildHeap(int n, unsigned short Heap[], unsigned short Hierarchy[]);

void moveDown(int i, int n, unsigned short Heap[], unsigned short Hierarchy[]);

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
 
  

  printf("n = %hu, q = %hu\n", n, q);
  for (int i = 0; i < n-1; i++) {
    printf("desc[%d] = %hu\n", i, desc[i]);
  }

  printf("size = %ld", sizeof(desc));

  return 0;
}

void buildHeap(int n, unsigned short Heap[], unsigned short Hierarchy[]){
  for (int i = n/2 + n%2; i > 0; i--) {
    moveDown(i, n , Heap[], Hierarchy[]);
  }
}

void moveDown(int n, unsigned short Heap[], unsigned short Hierarchy[]){

}
