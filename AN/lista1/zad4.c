#include <stdio.h>
#include <math.h>


int main(int argc, char const *argv[])
{
  double y0 = 1;
  double y1 = -1.0/9.0;

  printf("y0 = 1\ny1 = %lf\n", y1);
  
  for (int i = 0; i <= 48; i++)
  {
    double y2 = (80*y1/9.0) + y0;
    printf("y%d = %lf\n", i+2, y2);
    y0 = y1;
    y1 = y2;
  }
  
  return 0;
}
