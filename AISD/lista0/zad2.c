#include <stdio.h>

int main(void)
{
  int a;
  int b;
  scanf("%d %d", &a, &b);

  int counter = a + 2024 - a%2024;

  printf("counter = %d\n", counter);


  return 0;
}
