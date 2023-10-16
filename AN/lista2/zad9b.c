#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[])
{

  double x = 2;
  for (int k = 1; k < 50; k++)
  {
    double pot=pow(2,k);
    double div=pow(x/pot,2);
    x=sqrt(2*x*x/(1+sqrt(1-div)));
    printf("pi(%d) = %lf\n", k, x);
  }
  return 0;
}
