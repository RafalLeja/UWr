#include <stdio.h>
#include <math.h>

int main() {
  double a = 0.25;
  double b = 1000000.0;
  double c = 0.25;
  double x2liceum = (-b + (sqrt(pow(b, 2.0) - (4.0 * a * c)))) / (2.0 * a);
  double x2studia = (2.0 * c) / (- b - (sqrt(pow(b, 2.0) - (4.0 * a * c))));
  double result1 = a * pow(x2liceum, 2.0) + b * x2liceum + c; 
  double result2 = a * pow(x2studia, 2.0) + b * x2studia + c; 
  printf("%.6lf\n %.6lf\n", result1, result2);
  


}