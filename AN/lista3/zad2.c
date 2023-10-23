#include <stdio.h>
#include <math.h>

double f_k(double a, double b, double c, double x){
  return a*pow(x,2) + b*x + c;
}

void m0(double a, double b, double c){
  double delta = sqrt(pow(b,2)-(4*a*c));
  if (delta > 0)
  {
    //double x1 = (-b-delta)/(2*a);
    double x2 = (-b+delta)/(2*a);
    printf("m0 = %f \n", x2);
    printf("f(m0) = %f \n", f_k(a,b,c,x2));
  }else if (delta = 0)
  {
    double x0 = -b/(2*a);
    printf("m0 = %f\n", x0);
    printf("f(m0) = %f\n", f_k(a,b,c,x0));
  }
  else
  {
    printf("brak rozwiązań\n");
  }
}

void new_m0(double a, double b, double c){
  double delta = sqrt(pow(b,2)-(4*a*c));
  printf("%f\n", delta);
  if (delta > 0)
  {
    //double x1 = (-b-delta)/(2*a);
    double x2 = (2*c)/(-b-delta);
    printf("new_m0 = %f \n", x2);
    printf("f(m0) = %f \n", f_k(a,b,c,x2));
  }else if (delta = 0)
  {
    double x0 = -b/(2*a);

    printf("new_m0 = %f\n", x0);
    printf("f(m0) = %f\n", f_k(a,b,c,x0));
  }
  else
  {
    printf("brak rozwiązań\n");
  }
}

int main(int argc, char const *argv[])
{
  double a = 0.25;
  double b = 10000000;
  double c = 0.25;
  // printf("podaj a b c\n");
  // scanf("%lf %lf %lf", &a, &b, &c);
  
  m0(a,b,c);
  new_m0(a,b,c);
  
  

  return 0;
}
