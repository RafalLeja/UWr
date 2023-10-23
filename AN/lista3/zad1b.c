#include <stdio.h>
#include <math.h>

double f(double x){
  return log2(x)-2;
}

double new_f(double x){
  return log(x/4)/log(2);
}

int main(int argc, char const *argv[])
{
  double x = 4-(pow(10,-15));
  printf("f = %le\n", f(x),pow(x,3));
  printf("poprawione f = %le", new_f(x));

  FILE *data = fopen("data1b.txt", "w");
  fprintf(data, "#x f f2\n");
  for (int i = 3; i < 19; i++)
    fprintf(data, "%d %le %le\n", i, f(4-(pow(10,-i))), new_f(4-pow(10,-i)));
  fflush(data);
  fclose(data);

  FILE *gnuplot = popen("gnuplot -p", "w");
  fprintf(gnuplot, "set grid\n set logscale f 10\n");
  fprintf(gnuplot, "plot 'data1b.txt' using 1:2 t 'f' with lines, '' using 1:3 t 'new f' with lines\n");
  fflush(gnuplot);
  fclose(gnuplot);

  return 0;
}
