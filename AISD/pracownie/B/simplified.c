#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

const double INF = 1e15;

struct point {
  int x;
  int y;
};

void printPoints(const struct point *points, int n) {
  printf("Points:\n");
  for (int i = 0; i < n; i++) {
    printf("Point %d: x = %d, y = %d\n", i+1, points[i].x, points[i].y);
  }
}

double divAndConq(struct point *pointsX, struct point *pointsY, int n);
double stripSearch(struct point *points, int n);
double distance(const struct point *a, const struct point *b);
double triangle(const struct point *a, const struct point *b, const struct point *c);
int compX(const void *a, const void *b);
int compY(const void *a, const void *b);


int main()
{
  int n;
  scanf("%d", &n);

  struct point *pointsX = calloc(n, sizeof(struct point));
  struct point *pointsY = calloc(n, sizeof(struct point));
  // struct point *min = calloc(3, sizeof(struct point));

  for (int i = 0; i < n; i++) {
    scanf("%d %d", &pointsX[i].x, &pointsX[i].y);
    pointsY[i] = pointsX[i];
  }


  qsort(pointsX, n, sizeof(struct point), compX);
  qsort(pointsY, n, sizeof(struct point), compY);

  // printPoints(pointsX, n);

  // findMin(points, min, n);
  printf("%.*lf\n", DBL_DECIMAL_DIG, divAndConq(pointsX, pointsY, n));
  return 0;
}

double divAndConq(struct point *pointsX, struct point *pointsY, int n){
  if (n < 3)
  {
    return INF;
  }
  if (n < 6){
    return stripSearch(pointsX, n);
  }

  int mid = n/2;
  struct point *midPoint = calloc(1, sizeof(struct point));
  midPoint->x = (pointsX[mid-1].x + pointsX[mid].x) / 2;
  midPoint->y = (pointsX[mid-1].y + pointsX[mid].y) / 2;
  // printf("midPoint: %d %d\n", midPoint->x, midPoint->y);

  struct point *leftY = calloc(mid, sizeof(struct point));
  struct point *rightY = calloc(n-mid, sizeof(struct point));
  int l = 0, r = 0;
  for (int i = 0; i < n; i++)
  {
    if (compX(&pointsY[i], midPoint) < 0)
    {
      leftY[l++] = pointsY[i];
    } else {
      rightY[r++] = pointsY[i];
    }
  }

  double left = divAndConq(pointsX, leftY, mid);
  double right = divAndConq(pointsX + mid, rightY, n-mid);
  // printPoints(leftY, l);
  // printPoints(rightY, r);
  // printf("left: %f, right: %f\n", left, right);
  double min = left < right ? left : right;

  struct point *strip = calloc(n, sizeof(struct point));

  int j = 0;
  for (int i = 0; i < n; i++)
  {
    if (abs(pointsY[i].x - midPoint->x) < min/2)
    {
      strip[j++] = pointsY[i];
    }
  }
  left = stripSearch(strip, j);

  min = left < min ? left : min;


  free(midPoint);
  free(leftY);
  free(rightY);
  free(strip);
  return min;
}

double stripSearch(struct point *points, int n){
  double min_circ = INF;
  double tri = 0.0;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (i == j)
      {
        continue;
      }
      for (int k = 0; k < n; k++)
      {
        if (i == k || j == k)
        {
          continue;
        }
        tri = triangle(&points[i], &points[j], &points[k]);
        // printf("min_circ: %f, tri: %f\n", min_circ, tri);
        if (min_circ > tri)
        {
          min_circ = tri;
        }
      }
    }
  }

  return min_circ;
}

double distance(const struct point *a, const struct point *b){
  // printf("preSQRT %lf\n", sqrt((double) (a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y)) );
  const double x1 = a->x;
  const double x2 = b->x;
  const double y1 = a->y;
  const double y2 = b->y;
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double triangle(const struct point *a, const struct point *b, const struct point *c){
  double ab = distance(a, b);
  double bc = distance(b, c);
  double ca = distance(c, a);
  // printf("ab: %f, a.x: %d, a.y: %d, b.x: %d, b.y: %d\n", ab, a->x, a->y, b->x, b->y);
  return ab + bc + ca;
}

int compX(const void *a, const void *b){
  // printf("a.x: %d, b.x: %d\n", ((struct point*)a)->x, ((struct point*)b)->x);
  struct point *p1 = (struct point*)a;
  struct point *p2 = (struct point*)b;
  int out = (p1->x > p2->x) - (p1->x < p2->x);
  // printf("out: %d\n", out);
  if (out == 0)
  {
    return (p1->y > p2->y) - (p1->y < p2->y);
  }
  
  
  return out;
}

int compY(const void *a, const void *b){
  struct point *p1 = (struct point*)a;
  struct point *p2 = (struct point*)b;
  int out = (p1->y > p2->y) - (p1->y < p2->y);
  if (out == 0)
  {
    return (p1->x > p2->x) - (p1->x < p2->x);
  }
  
  return out;
}
