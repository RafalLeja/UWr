#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[])
{
  double a = 2;
  double x0 = 0.000001;

  for (int i = 0; i < 30; i++)
  {
    x0 = 0.5*x0*(3-a*x0*x0);
    printf("krok %d = %.10lf\n", i+1, x0);
  }
  

  FILE *data = fopen("data6.txt", "w");
  fprintf(data, "#x f f2\n");
  for (double i = -1; i < 1; i += 0.001)
    fprintf(data, "%lf %lf %lf %lf\n", i, 1/pow(i,2)-2);
  fflush(data);
  fclose(data);

  FILE *gnuplot = popen("gnuplot -p", "w");
  fprintf(gnuplot, "set grid\n set yrange [-10:50]\n");
  fprintf(gnuplot, "plot 'data6.txt' using 1:2 t 'f' with lines\n");
  fflush(gnuplot);
  fclose(gnuplot);

  return 0;
}
