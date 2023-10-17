#include <stdio.h>
#include <math.h>

double f(double x){
  double pot = pow(x, 14);
  pot = sqrt(pot+1)+1;
  x = 4046/pot;
  return x;
}

int main(int argc, char const *argv[])
{

  printf("0.001 = %e\n", pow(0.001, 14)+1);
  printf("f(0.001) = %e", f(0.001));
  return 0;
}
