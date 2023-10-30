#include <stdio.h>
#include <math.h>

double f(double x, double R){
  return x*(2-x*R);
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
  printf("%d\n", newtonP(0.3, 2, f));

  FILE *data = fopen("data5.txt", "w");
  fprintf(data, "#x f f2\n");
  for (int i = 1; i < 100; i++)
    fprintf(data, "%d %d %d %d\n", i, newtonP(1/4+(i*0.5/100), 2, f), newtonP(1/20+(i*0.1/100), 10, f), newtonP(1/200+(i*0.01/100), 100, f));
  fflush(data);
  fclose(data);

  FILE *gnuplot = popen("gnuplot -p", "w");
  fprintf(gnuplot, "set grid\n");
  fprintf(gnuplot, "plot 'data5.txt' using 1:2 t 'R = 2' with lines, '' using 1:3 t 'R = 10' with lines, '' using 1:4 t 'R = 100' with lines\n");
  fflush(gnuplot);
  fclose(gnuplot);

  return 0;
}
