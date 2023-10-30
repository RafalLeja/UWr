#include <stdio.h>
#include <math.h>

double f(double x, double a){
  return 0.5*x*(3-a*x*x);
}

double newton(double x0, double a,double n, double (*func)(double, double)){
  for (int i = 0; i < n; i++)
  {
    x0 = func(x0, a);
  }
  return x0;
}

int newtonP(double x0, double R, double (*func)(double, double)){
  int n = 0;
  double xn = 0;
  while (xn-x0 != 0 && n < 20)
  {
    xn = x0;
    n++;
    x0 = func(x0, R);
    // printf("%e\n",xn-x0);
  }
  return n;
}

int main(int argc, char const *argv[])
{
  // double a = 2;
  // double x0 = 0.5;

  // for (int i = 0; i < 30; i++)
  // {
  //   x0 = 0.5*x0*(3-a*x0*x0);
  //   printf("krok %d = %.10lf\n", i+1, x0);
  // }
  
  printf("1/sqrt(2) = %lf, 1/sqrt(100) = %lf\n", newton(1, 2, 20, f), newton(0.01, 100, 20, f));

  FILE *data = fopen("data6.txt", "w");
  fprintf(data, "#x f f2\n");
  for (double i = -2; i < 2; i+= 0.01)
    fprintf(data, "%lf %lf %d\n", i, fabs(newton(i, 2, 5, f)), newtonP(i, 2, f));
  fflush(data);
  fclose(data);

  FILE *gnuplot = popen("gnuplot -p", "w");
  fprintf(gnuplot, "set grid\n set yrange [-10:50]\n");
  fprintf(gnuplot, "plot 'data6.txt' using 1:2 t 'x0' with lines, '' using 1:3 t 'iteracje' with lines\n");
  fflush(gnuplot);
  fclose(gnuplot);

  return 0;
}
