#include <stdio.h>
#include <math.h>

double f(double x){
  return x-0.49;
}

int main(int argc, char const *argv[])
{
  double alpha = 0.49;
  double a = 0;
  double b = 1;
  printf("n | szacowany blad | rzeczywisty blad\n");
  for (int i = 0; i < 6; i++)
  {
    double m =(a+b)/2;
    printf("%d | %lf | %lf\n", i, 1/pow(2,i+1), fabs(0.49-m));
    if (f(m) > 0)
    {
      b = m;
    }else
    {
      a = m;
    }
  }
  return 0;
}
