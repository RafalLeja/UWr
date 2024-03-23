#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <array>
#include <float.h>
using namespace std;

const int SHIFT = 100000000;

struct Point {
  int x,y;
  Point() {}
  Point(int x,int y):x(x),y(y) {}
};

inline Point middle(const Point &a, const Point &b) {
  return Point((a.x+b.x)/2, (a.y+b.y)/2);
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

double distance(Point a, Point b) {
  return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double perimeter(Point a, Point b, Point c) {
  return distance(a, b) + distance(b, c) + distance(c, a);
}

double divAndConq(int n, const Point points[], const vector<Point> &pointsByY, array<Point, 3> &min) {
  if(n<3) return DBL_MAX;
  int left = n/2;
  int right = n-left;
  Point split = middle(points[left-1], points[left]);
  vector<Point> pointsByYLeft, pointsByYRight;
  array<Point, 3> minLeft, minRight;
  pointsByYLeft.reserve(left);
  pointsByYRight.reserve(right);
  for (int i = 0; i < n; i++){
    if(compareX(pointsByY[i], split))
      pointsByYLeft.push_back(pointsByY[i]);
    else
      pointsByYRight.push_back(pointsByY[i]);
  }
  double res = DBL_MAX;
  double leftRes = divAndConq(left, points, pointsByYLeft, minLeft);
  double rightRes = divAndConq(right, points+left, pointsByYRight, minRight);
  if(leftRes < rightRes) {
    res = leftRes;
    min = minLeft;
  } else {
    res = rightRes;
    min = minRight;
  }
  static vector<Point> closeToTheLine;
  int margin = (res > DBL_MAX/2) ? 2*SHIFT : int(res/2);
  closeToTheLine.clear();
  closeToTheLine.reserve(n);
  int start = 0;
  for(int i=0;i<n;++i) {
    Point p = pointsByY[i];
    if(abs(p.x - split.x) > margin) continue;
    while(start < closeToTheLine.size() &&
          p.y - closeToTheLine[start].y > margin) ++start;
    for(int i=start;i<closeToTheLine.size();++i) {
      for(int j=i+1;j<closeToTheLine.size();++j) {
        if(perimeter(p, closeToTheLine[i], closeToTheLine[j]) < res) {
          res = perimeter(p, closeToTheLine[i], closeToTheLine[j]);
          min[0] = p;
          min[1] = closeToTheLine[i];
          min[2] = closeToTheLine[j];
        }
      }
    }
    closeToTheLine.push_back(p);
  }
  return res;
}

int main() {
  int n; 
  scanf("%d", &n);
  
  vector<Point> points;
  points.reserve(n);
  array<Point, 3> min;
  
  for (int i = 0; i < n; i++) {
    int x,y; scanf("%d %d", &x, &y);
    points.push_back(Point(2*x-SHIFT,2*y-SHIFT)); // żeby uniknąć tracenia liczb znaczących 
  }
  vector<Point> pointsByY = points;
  
  sort(points.begin(), points.end(), compareX);
  sort(pointsByY.begin(), pointsByY.end(), compareY);

  double res = divAndConq(points.size(), &points[0], pointsByY, min);

  // printf("%.15e\n", res/2);
  for(int i=0;i<3;++i) {
    printf("%d %d\n", min[i].x/2, min[i].y/2);
  }
  }