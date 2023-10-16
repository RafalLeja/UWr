#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[])
{

  double x = 2;
  for (int k = 1; k < 50; k++)
  {
    double pot=pow(2,k);
    x=pot*sqrt(2*(1-sqrt(1-pow(x/pot,2))));
    printf("pi(%d) = %f\n", k, x);
  }
  return 0;
}
