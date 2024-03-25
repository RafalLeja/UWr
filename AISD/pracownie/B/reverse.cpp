#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
#include <array>
#include <float.h>
#include <cstdint>
using namespace std;

struct Point {
  int x,y;
};

double distance(Point a, Point b) {
  double x1 = a.x;
  double y1 = a.y;
  double x2 = b.x;
  double y2 = b.y;
  return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

double perimeter(Point a, Point b, Point c) {
  return distance(a, b) + distance(b, c) + distance(c, a);
}

bool compareX(Point a, Point b) {
  if (a.x == b.x) {
    return a.y < b.y;
  }
  return a.x < b.x;
}

bool compareY(Point a, Point b) {
  if (a.y == b.y) {
    return a.x < b.x;
  }
  return a.y < b.y;
}

double divAndConq(int n, const Point points[], const vector<Point> &pointsByY, array<Point, 3> &minArr) {
  if(n < 3) {
    return DBL_MAX;
  }

  int mid = n/2;

  Point midPoint = {
    (points[mid-1].x + points[mid].x)/2,
    (points[mid-1].y + points[mid].y)/2
  };

  vector<Point> pointsByYLeft, pointsByYRight;
  pointsByYLeft.reserve(mid);
  pointsByYRight.reserve(n-mid);
  array<Point, 3> minLeft, minRight;

  for (int i = 0; i < n; i++){
    if(compareX(pointsByY[i], midPoint))
      pointsByYLeft.push_back(pointsByY[i]);
    else
      pointsByYRight.push_back(pointsByY[i]);
  }

  double res = DBL_MAX;
  double leftRes =  divAndConq(mid, points, pointsByYLeft, minLeft);
  double rightRes = divAndConq(n-mid, points+mid, pointsByYRight, minRight);
  
  if (leftRes < rightRes) {
    res = leftRes;
    minArr = minLeft;
  } else {
    res = rightRes;
    minArr = minRight;
  }

  int margin = (res > DBL_MAX/2) ? INT32_MAX : res/2;

  vector<Point> box;
  box.reserve(n);

  int first = 0;
  int last = 0;

  for(int i = 0; i < n; i++) {

    Point p = pointsByY[i];
    
    if(abs(p.x - midPoint.x) > margin) {
      continue;
    }

    while(first < last && p.y - box[first].y > margin) {
      first++;
    }

    for(int j = first; j < last; j++) {
      for(int k = j+1; k < last; k++) {
        if(perimeter(p, box[j], box[k]) < res) {
          res = perimeter(p, box[j], box[k]);
          minArr[0] = p;
          minArr[1] = box[j];
          minArr[2] = box[k];
        }
      }
    }
    box.push_back(p);
    last++;
  }

  return res;
}

int main() {
  int n; scanf("%d", &n);
  vector<Point> points;
  array<Point, 3> min;
  points.reserve(n);
  for (int i = 0; i < n; i++) {
    int x,y; 
    scanf("%d %d", &x, &y);
    points.push_back({x,y});
  }
  

  sort(points.begin(), points.end(), compareX);
  vector<Point> pointsByY = points;
  sort(pointsByY.begin(), pointsByY.end(), compareY);
  
  divAndConq(points.size(), &points[0], pointsByY, min);

  for(int i=0;i<3;++i) {
    printf("%d %d\n", min[i].x, min[i].y);
  }
  
}