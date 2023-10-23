#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

double f(double x){
  double arcctg = M_PI_2 - atan(x);
  return pow(x,-3)*(M_PI_2-x-arcctg);
}

double new_f(double x){
  return ((3*x*x)-5)/15;
}

int main(int argc, char const *argv[])
{
  double x = 0.000001;
  printf("f = %e\n", f(x));
  printf("poprawione f = %e", new_f(x));

  FILE *data = fopen("data1c.txt", "w");
  fprintf(data, "#x f f2\n");
  // for (double i = 0.001; i > 0.00000001; i /= 10)
  for (double i = -0.00005; i < 0.00005; i += 0.000001)
    fprintf(data, "%lf %lf %lf\n", i, f(i), new_f(i));
  fflush(data);
  fclose(data);

  FILE *gnuplot = popen("gnuplot -p", "w");
  fprintf(gnuplot, "set grid\n");
  //fprintf(gnuplot, "set nonlinear x via log10(x) inverse 10**x\n set xtics log\n");
  fprintf(gnuplot, "plot 'data1c.txt' using 1:2 t 'f' with lines, '' using 1:3 t 'new f' with lines\n");
  fflush(gnuplot);
  fclose(gnuplot);

  return 0;
}
