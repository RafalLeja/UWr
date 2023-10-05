#include <stdio.h>
#include <math.h>

double f_d(double x){
  double pot = pow(x, 2);
  x = 1-cos(17*x);
  x = 14*x/pot;
  return x;
}

float f_f(float x){
  float pot = powf(x, 2);
  x = 1-cosf(17*x);
  x = 14*x/pot;
  return x;
}

int main(int argc, char const *argv[])
{

  double d = 11;
  float f = 11;
  for (double i = 11; i < 21; i++)
  {
    printf("f_d(%.0f) = %f ", d, f_d(d));
    printf("f_f(%.0f) = %f\n", f, f_f(f));
    d++;
    f++;
  }

  return 0;
}
