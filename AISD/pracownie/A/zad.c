// Rafał Leja
// 340879
// MBa

#include <stdio.h>
#include <stdlib.h>

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

// int isParent(int a, int b, unsigned short *hierarchy){
//   if (a == 1 || a == b) return 1;
//   if (b == 1) return 0;
//   return isParent(a, hierarchy[b-2], hierarchy);
// }