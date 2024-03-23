#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <array>
#include <float.h>
using namespace std;
template<class T> inline int size(const T&c) { return c.size();}

const int BILLION = 1000000000;

struct Point {
  int x,y;
  Point() {}
  Point(int x,int y):x(x),y(y) {}
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

double divAndConq(int n, const Point points[],
            const vector<Point> &pointsByY, array<Point, 3> &minArr) {
  if(n<3) return DBL_MAX;
  int mid = n/2;

  Point midPoint = Point(
    (points[mid-1].x + points[mid].x)/2,
    (points[mid-1].y + points[mid].y)/2
  );

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

  // static vector<Point> closeToTheLine;
  // int margin = (res > DBL_MAX/2) ? 2*BILLION : int(res/2);
  // closeToTheLine.clear();
  // closeToTheLine.reserve(n);
  // int start = 0;
  // for(int i=0;i<n;++i) {
  //   Point p = pointsByY[i];
  //   if(abs(p.x - midPoint.x) > margin) continue;
  //   while(start < closeToTheLine.size() &&
  //         p.y - closeToTheLine[start].y > margin) ++start;
  //   for(int i=start;i<closeToTheLine.size();++i) {
  //     for(int j=i+1;j<closeToTheLine.size();++j) {
  //       if(perimeter(p, closeToTheLine[i], closeToTheLine[j]) < res) {
  //         res = perimeter(p, closeToTheLine[i], closeToTheLine[j]);
  //         minArr[0] = p;
  //         minArr[1] = closeToTheLine[i];
  //         minArr[2] = closeToTheLine[j];
  //       }
  //     }
  //   }
  //   closeToTheLine.push_back(p);
  // }

  static vector<Point> strip;
  int margin = int(res/2);
  strip.clear();
  strip.reserve(n);
  for(int i=0;i<n;++i) {
    if (abs(pointsByY[i].x - midPoint.x) <= margin) {
      strip.push_back(pointsByY[i]);
    }
  }

  for (int i = 0; i < strip.size(); i++) {
    for (int j = i+1; j < strip.size(); j++) {
      for (int k = j+1; k < strip.size(); k++) {
        if (perimeter(strip[i], strip[j], strip[k]) < res) {
          res = perimeter(strip[i], strip[j], strip[k]);
          minArr[0] = strip[i];
          minArr[1] = strip[j];
          minArr[2] = strip[k];
        }
      }
    }
  }

  return res;
}

int main() {
  int n; scanf("%d", &n);
  vector<Point> points;
  array<Point, 3> min;
  points.reserve(n);
  for (int i = 0; i < n; i++) {
    int x,y; scanf("%d%d", &x, &y);
    points.push_back(Point(2*x-BILLION,2*y-BILLION));
  }
  
  sort(points.begin(), points.end(), compareX);
  vector<Point> pointsByY = points;
  sort(pointsByY.begin(), pointsByY.end(), compareY);
  
  double res = divAndConq(points.size(), &points[0], pointsByY, min);

  for(int i=0;i<3;++i) {
    printf("%d %d\n", min[i].x/2, min[i].y/2);
  }
  
}