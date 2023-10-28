#include <stdio.h>
#include <math.h>

double f(double x){
  return pow(x,4) - log(x+4);
}

double g(double x){
  return pow(x,4);
}

double h(double x){
  return log(x+4);
}

double bisekcja(double a, double b, int n, double (*func)(double) ){
  double m =(a+b)/2;
  int inc = func(a) < func(b);
  for (int i = 0; i <= n; i++)
  {
    if (func(m) > 0 && inc || func(m) < 0 && !inc)
    {
      b = m;
    }else
    {
      a = m;
    }
    m =(a+b)/2;
  }

  return m;
}

int main(int argc, char const *argv[])
{
  printf("x1 = %.9lf, x2 = %0.9lf", bisekcja(-1.5, -0.5, 26, f), bisekcja(0.5, 1.5, 26, f));

  FILE *data = fopen("data1a.txt", "w");
  fprintf(data, "#x f f2\n");
  for (double i = -2; i < 2; i += 0.01)
    fprintf(data, "%lf %lf %lf %lf\n", i, f(i), g(i), h(i));
  fflush(data);
  fclose(data);

  FILE *gnuplot = popen("gnuplot -p", "w");
  fprintf(gnuplot, "set grid\n");
  fprintf(gnuplot, "plot 'data1a.txt' using 1:2 t 'f' with lines, '' using 1:3 t 'g' with lines, '' using 1:4 t 'h' with lines\n");
  fflush(gnuplot);
  fclose(gnuplot);

  return 0;
}
