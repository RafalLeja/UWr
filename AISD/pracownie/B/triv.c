#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point {
  int x;
  int y;
};

double distance(struct point *a, struct point *b);
double triange(struct point *a, struct point *b, struct point *c);

int main()
{
  int n;
  scanf("%d", &n);

  struct point *points = malloc(n * sizeof(struct point));
  struct point *min[3];

  for (int i = 0; i < n; i++) {
    scanf("%d %d", &points[i].x, &points[i].y);
  }
  
  min[0] = &points[0];
  min[1] = &points[1];
  min[2] = &points[2];

  double min_distance = triange(&points[0], &points[1], &points[2]);
  for (int x = 0; x < n; x++)
  {
    for (int y = 0; y < n; y++)
    {
      if (x == y) continue;
      for (int z = 0; z < n; z++)
      {
        if (z == x || z == y) continue;
        
        double tri = triange(&points[x], &points[y], &points[z]);
        if (min_distance > tri)
        {
          min[0] = &points[x];
          min[1] = &points[y];
          min[2] = &points[z];
          min_distance = tri;
        }
        
  }}}

  for (int i = 0; i < 3; i++)
  {
    printf("%d %d\n", min[i]->x, min[i]->y);
  }
  

  return 0;
}

double distance(struct point *a, struct point *b){
  return sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
}

double triange(struct point *a, struct point *b, struct point *c){
  double ab = distance(a, b);
  double bc = distance(b, c);
  double ca = distance(c, a);
  return ab + bc + ca;
}