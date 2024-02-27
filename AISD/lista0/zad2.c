// Rafał Leja
// 340879
// MBa

#include <stdio.h>

int main(void)
{
  int a, b;
  scanf("%d %d", &a, &b);

  int start = a + 2023 - (a-1)%2024;

  for (int i = start; i <= b; i+=2024) {
    printf("%d\n", i);
  }

  return 0;
}
