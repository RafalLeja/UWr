#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point {
  int x;
  int y;
};

void divAndConq(struct point *points, struct point *minTri, int n);
void find_min(struct point *points, struct point *minTri, int n);
double distance(struct point *a, struct point *b);
double triangle(struct point *a, struct point *b, struct point *c);
int compX(const void *a, const void *b);
int compY(const void *a, const void *b);


int main()
{
  int n;
  scanf("%d", &n);

  struct point *points = calloc(n, sizeof(struct point));
  struct point *min = calloc(3, sizeof(struct point));

  for (int i = 0; i < n; i++) {
    scanf("%d %d", &points[i].x, &points[i].y);
  }


  qsort(points, n, sizeof(struct point), compX);
  
  // find_min(points, min, n);
  divAndConq(points, min, n);

  for (int i = 0; i < 3; i++)
  {
    printf("%d %d\n", min[i].x, min[i].y);
  }
  

  return 0;
}

void divAndConq(struct point *points, struct point *minTri, int n){
  if (n < 50)
  {
    find_min(points, minTri, n);
    return;
  }

  int mid = n/2;

  struct point *left = calloc(mid, sizeof(struct point));
  struct point *right = calloc(n-mid, sizeof(struct point));
  struct point *minLeft = calloc(3, sizeof(struct point));
  struct point *minRight = calloc(3, sizeof(struct point));

  for (int i = 0; i < mid; i++)
  {
    left[i] = points[i];
  }
  for (int i = mid; i < n; i++)
  {
    right[i-mid] = points[i];
  }

  divAndConq(left, minLeft, mid);
  divAndConq(right, minRight, n-mid);

  double min_circ;
  if (triangle(&minLeft[0], &minLeft[1], &minLeft[2]) < triangle(&minRight[0], &minRight[1], &minRight[2]))
  {
    min_circ = triangle(&minLeft[0], &minLeft[1], &minLeft[2]);
    minTri[0] = minLeft[0];
    minTri[1] = minLeft[1];
    minTri[2] = minLeft[2];
  }
  else
  {
    min_circ = triangle(&minRight[0], &minRight[1], &minRight[2]);
    minTri[0] = minRight[0];
    minTri[1] = minRight[1];
    minTri[2] = minRight[2];
  }

  int j = 0;
  for (int i = 0; i < n; i++)
  {
    if (abs(points[i].x - points[mid].x) < min_circ / 2.0)
    {
      left[j++] = points[i];
    }
  }
  
  find_min(left, minLeft, j);
  if (triangle(&minLeft[0], &minLeft[1], &minLeft[2]) < min_circ)
  {
    min_circ = triangle(&minLeft[0], &minLeft[1], &minLeft[2]);
    minTri[0] = minLeft[0];
    minTri[1] = minLeft[1];
    minTri[2] = minLeft[2];
  }

}

void find_min(struct point *points, struct point *minTri, int n){
  minTri[0] = points[0];
  minTri[1] = points[1];
  minTri[2] = points[2];

  double min_circ = triangle(&points[0], &points[1], &points[2]);
  for (int x = 0; x < n; x++)
  {
    for (int y = 0; y < n; y++)
    {
      if (x == y) continue;
      for (int z = 0; z < n; z++)
      {
        if (z == x || z == y) continue;
        
        double tri = triangle(&points[x], &points[y], &points[z]);
        if (min_circ > tri)
        {
          minTri[0] = points[x];
          minTri[1] = points[y];
          minTri[2] = points[z];
          min_circ = tri;
        }
        
  }}}
}

double distance(struct point *a, struct point *b){
  return sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
}

double triangle(struct point *a, struct point *b, struct point *c){
  double ab = distance(a, b);
  double bc = distance(b, c);
  double ca = distance(c, a);
  return ab + bc + ca;
}

int compX(const void *a, const void *b){
  struct point *p1 = (struct point *)a;
  struct point *p2 = (struct point *)b;
  return p1->x - p2->x;
}

int compY(const void *a, const void *b){
  struct point *p1 = (struct point *)a;
  struct point *p2 = (struct point *)b;
  return p1->y - p2->y;
}