#include <stdio.h>
#include <math.h>

double f(double x){
  double pot = pow(x, 14);
  x = sqrt(pot+1)-1;
  x = 4046*x/pot;
  return x;
}

int main(int argc, char const *argv[])
{
  printf("f(0.001) = %e", f(0.001));
  return 0;
}
