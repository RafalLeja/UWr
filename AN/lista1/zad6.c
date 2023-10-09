#include <stdio.h>
#include <math.h>

double pi(int n){
  double pi = 0;
  for (int i = 0; i < n; i++)
  {
    pi += (pow(-1, i)/(2*i +1));
  }
  return pi*4;
}

float pif(int n){
  float pi = 0;
  for (int i = 0; i < n; i++)
  {
    pi += (powf(-1, i)/(2*i +1));
  }
  return pi*4;
}

int main(int argc, char const *argv[])
{
  
  printf("pi = %lf\n", pi(2*pow(10,6)));
  printf("pif = %f", pif(2*powf(10,6)));
  return 0;
}
