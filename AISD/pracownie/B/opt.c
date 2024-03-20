#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

struct point {
  int x;
  int y;
};

void printPoints(struct point *points, int n) {
  printf("Points:\n");
  for (int i = 0; i < n; i++) {
    printf("Point %d: x = %d, y = %d\n", i+1, points[i].x, points[i].y);
  }
}

double divAndConq(struct point *pointsX, struct point *pointsY, struct point *minTri, int n);
double findMin(struct point *points, struct point *minTri, int n);
double stripSearch(struct point *points, struct point *minTri, int n, double min_circ);
double distance(struct point *a, struct point *b);
double triangle(struct point *a, struct point *b, struct point *c);
int compX(const void *a, const void *b);
int compY(const void *a, const void *b);


int main()
{
  int n;
  scanf("%d", &n);

  struct point *pointsX = calloc(n, sizeof(struct point));
  struct point *pointsY = calloc(n, sizeof(struct point));
  struct point *min = calloc(3, sizeof(struct point));

  for (int i = 0; i < n; i++) {
    scanf("%d %d", &pointsX[i].x, &pointsX[i].y);
    pointsY[i] = pointsX[i];
  }


  qsort(pointsX, n, sizeof(struct point), compX);
  qsort(pointsY, n, sizeof(struct point), compY);

  // printPoints(pointsX, n);

  // findMin(points, min, n);
  divAndConq(pointsX, pointsY, min, n);

  for (int i = 0; i < 3; i++)
  {
    printf("%d %d\n", min[i].x, min[i].y);
  }
  

  return 0;
}

double divAndConq(struct point *pointsX, struct point *pointsY, struct point *minTri, int n){
  if (n < 3)
  {
    return DBL_MAX;
  }

  int mid = n/2;
  struct point *midPoint = calloc(1, sizeof(struct point));
  midPoint->x = (pointsX[mid-1].x + pointsX[mid].x)/2;
  midPoint->y = (pointsX[mid-1].y + pointsX[mid].y)/2;
  printf("midPoint: x: %d, y: %d\n", midPoint->x, midPoint->y);
  printPoints(pointsX, n);

  struct point *leftX = calloc(mid, sizeof(struct point));
  struct point *leftY = calloc(mid, sizeof(struct point));
  struct point *rightX = calloc(n-mid, sizeof(struct point));
  struct point *rightY = calloc(n-mid, sizeof(struct point));
  struct point *minLeft = calloc(3, sizeof(struct point));
  struct point *minRight = calloc(3, sizeof(struct point));

  int l = 0;
  int r = 0;
  for (int i = 0; i < n; i++)
  {
    if (i < mid)
    {
      leftX[i] = pointsX[i];
    }
    else
    {
      rightX[i-mid] = pointsX[i];
    }
    if (compX(&pointsY[i], midPoint) < 0)
    {
      leftY[l++] = pointsY[i];
    }
    else
    {
      rightY[r++] = pointsY[i];
    }
  }

  double leftRes = divAndConq(leftX, leftY, minLeft, mid);
  double rightRes = divAndConq(rightX, rightY, minRight, n-mid);

  double min_circ = DBL_MAX;
  if (leftRes < rightRes)
  {
    min_circ = leftRes;
    minTri[0] = minLeft[0];
    minTri[1] = minLeft[1];
    minTri[2] = minLeft[2];
  }
  else
  {
    min_circ = rightRes;
    minTri[0] = minRight[0];
    minTri[1] = minRight[1];
    minTri[2] = minRight[2];
  }

  l = 0;
  for (int i = 0; i < n; i++)
  {
    if (abs(pointsY[i].x - pointsY[mid].x) < min_circ / 2.0)
    {
      leftY[l++] = pointsY[i];
    }
  }
  
  // findMin(left, minLeft, j);
  leftRes = stripSearch(leftY, minLeft, l, min_circ);
  if (leftRes < min_circ)
  {
    min_circ = leftRes;
    minTri[0] = minLeft[0];
    minTri[1] = minLeft[1];
    minTri[2] = minLeft[2];
  }

  return min_circ;
}

double findMin(struct point *points, struct point *minTri, int n){
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
  return min_circ;
}

double stripSearch(struct point *points, struct point *minTri, int n, double min_circ){
  if (n < 3)
  {
    return DBL_MAX;
  }
  // printPoints(points, n);
  minTri[0] = points[0];
  minTri[1] = points[1];
  minTri[2] = points[2];

  for (int i = 0; i < n; i++)
  {
    for (int j = i+1; j < n && points[j].y - points[i].y < min_circ ; j++)
    {
      for (int k = j+1; k < n && points[k].y - points[i].y < min_circ ; k++)
      {
        double tri = triangle(&points[i], &points[j], &points[k]);
        // printf("min_circ: %f, tri: %f\n", min_circ, tri);
        if (min_circ > tri)
        {
          minTri[0] = points[i];
          minTri[1] = points[j];
          minTri[2] = points[k];
          min_circ = tri;
        }
      }
    }
  }

  return min_circ;
}

double distance(struct point *a, struct point *b){
  // printf("preSQRT %lf\n", sqrt((double) (a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y)) );
  return sqrt((double) (a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
}

double triangle(struct point *a, struct point *b, struct point *c){
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
