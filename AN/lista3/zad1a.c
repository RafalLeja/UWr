#include <stdio.h>
#include <math.h>

double f(double x){
  return pow(pow(x,3) + sqrt(pow(x,6)+4092529),-1);
}

double new_f(double x){
  return (sqrt(pow(x,6)+(2023*2023)) - pow(x,3))/ (2023*2023);
}

int main(int argc, char const *argv[])
{
  double x = -6000;
  printf("f = %e, 1/f = %e\n", f(x),pow(x,3) + sqrt(pow(x,6)+4092529));
  printf("poprawione f = %e", new_f(x));

  FILE *data = fopen("data1a.txt", "w");
  fprintf(data, "#x f f2\n");
  for (int i = -7000; i < 500; i += 100)
    fprintf(data, "%d %lf %lf\n", i, f(i), new_f(i));
  fflush(data);
  fclose(data);

  FILE *gnuplot = popen("gnuplot -p", "w");
  fprintf(gnuplot, "set grid\n");
  fprintf(gnuplot, "plot 'data1a.txt' using 1:2 t 'f' with lines, '' using 1:3 t 'new f' with lines\n");
  fflush(gnuplot);
  fclose(gnuplot);

  return 0;
}
