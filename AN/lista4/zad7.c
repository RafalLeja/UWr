#include <stdio.h>
#include <math.h>
#define N 3
#define A 2

double f(double x){
  return (x*x+A)/(2*x);
}

double newton(double x0, double (*func)(double)){
  for (int i = 0; i < N; i++)
  {
    x0 = func(x0);
  }
  return x0;
}

int main(int argc, char const *argv[])
{
  double a = 2;
  double x0 = 1;

  for (int i = 0; i < N; i++)
  {
    x0 = x0-((x0*x0-a)/(2*x0));
    printf("krok %d = %.10lf\n", i+1, x0);
  }
  

  FILE *data = fopen("data7.txt", "w");
  fprintf(data, "#x f f2\n");
  for (double i = -20; i < 20; i += 0.01)
    fprintf(data, "%lf %lf\n", i, fabs(newton(i, f)));
  fflush(data);
  fclose(data);

  FILE *gnuplot = popen("gnuplot -p", "w");
  fprintf(gnuplot, "set grid\n set yrange [0:5]\n");
  fprintf(gnuplot, "plot 'data7.txt' using 1:2 t 'F3(x)' with lines\n");
  fflush(gnuplot);
  fclose(gnuplot);

  return 0;
}
