#include <iostream> 
#include <vector>   
#include <algorithm>
#include <cmath>
#include <cfloat>
using namespace std;

#define BIG 1000000000
const double INF = 1e20;


struct point {
  int x, y;
  point(int x, int y) : x(x), y(y) {}
  point() {}
};

void printPoints(vector<point> &points) {
  printf("Points:\n");
  for (int i = 0; i < points.size(); i++) {
    cout << points[i].x << " " << points[i].y << endl;
  }
}

bool compareX(point a, point b) {
  if (a.x == b.x) {
    return a.y < b.y;
  }
  return a.x < b.x;
}

bool compareY(point a, point b) {
  if (a.y == b.y) {
    return a.x < b.x;
  }
  return a.y < b.y;
}

struct CmpX {
  inline bool operator()(const point &a, const point &b) {
    if(a.x != b.x) return a.x < b.x;
    return a.y < b.y;
  }
} cmpx;

struct CmpY {
  inline bool operator()(const point &a, const point &b) {
    if(a.y != b.y) return a.y < b.y;
    return a.x < b.x;
  }
} cmpy;

double distance(point a, point b) {
  return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double perimeter(point a, point b, point c) {
  return distance(a, b) + distance(b, c) + distance(c, a);
}

double searchStrip(vector<point> &strip, int n, double d) {
  double minPerim = d;
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n && strip[j].y - strip[i].y < minPerim; j++) {
      for (int k = j+1; k < n && strip[k].y - strip[i].y < minPerim; k++) {
        double p = perimeter(strip[i], strip[j], strip[k]);
        if (p < minPerim) {
          minPerim = p;
        }
      }
    }
  }

  // static vector<point> closeToTheLine;
  // closeToTheLine.clear();
  // closeToTheLine.reserve(n);
  // int start = 0;
  // for(int i=0;i<n;++i) {
  //   point p = strip[i];
  //   if(abs(p.x - split.x) > d) continue;
  //   while(start < closeToTheLine.size() &&
  //         p.y - closeToTheLine[start].y > d) ++start;
  //   for(int i=start;i<closeToTheLine.size();++i) {
  //     for(int j=i+1;j<closeToTheLine.size();++j) {
  //       double perim = perimeter(p, closeToTheLine[i], closeToTheLine[j]);
  //       if (perim < minPerim) {
  //         minPerim = perim;
  //         min[0] = p;
  //         min[1] = closeToTheLine[i];
  //         min[2] = closeToTheLine[j];
  //       }                         
  //     }
  //   }
  //   closeToTheLine.push_back(p);
  // }

  return minPerim;
}

double divAndConq(vector<point> &pointsX, vector<point> &pointsY, int n) {
  if (n < 3) {
    return INF;
  }

  int mid = (n) / 2;
  point midPoint = point(
    (pointsX[mid-1].x + pointsX[mid].x)/2,
    (pointsX[mid-1].y + pointsX[mid].y)/2);

  vector<point> leftY(mid);
  vector<point> rightY(n - mid);
  // vector<point> leftMin(3);
  // vector<point> rightMin(3);
  vector<point> strip(n);

  int li = 0, ri = 0;
  for (int i = 0; i < n; i++) {
    if (cmpx(pointsY[i], midPoint)) {
      leftY[li++] = pointsY[i];
    } else {
      rightY[ri++] = pointsY[i];
    }
  }
  printf("l: %d, r: %d\n", leftY.size(), rightY.size() );

  double minPerim = INF;
  double leftRes = divAndConq(pointsX, leftY, mid);
  double rightRes = divAndConq(pointsX, rightY, n - mid);
  
  if (leftRes < minPerim) {
    minPerim = leftRes;
    // min[0] = leftMin[0];
    // min[1] = leftMin[1];
    // min[2] = leftMin[2];
  }
  if (rightRes < minPerim) {
    minPerim = rightRes;
    // min[0] = rightMin[0];
    // min[1] = rightMin[1];
    // min[2] = rightMin[2];
  }

  // int width;
  // if (minPerim > DBL_MAX/2) {
  //   width = pow(10, 7)*2;
  // }
  // else {
  //   width = minPerim/2;
  // }

  // int j = 0;
  // for (int i = 0; i < n; i++) {
  //   if (abs(pointsY[i].x - midPoint.x) < width) {
  //     strip[j++] = pointsY[i];
  //   }
  // }

  static vector<point> closeToTheLine;
  int width = (minPerim > INF/2) ? 2*BIG : int(minPerim/2);
  closeToTheLine.clear();
  closeToTheLine.reserve(n);
  int start = 0;
  for(int i=0;i<n;++i) {
    point p = pointsY[i];
    if(abs(p.x - midPoint.x) > width) continue;
    while(start < closeToTheLine.size() &&
          p.y - closeToTheLine[start].y > width) ++start;
    for(int i=start;i<closeToTheLine.size();++i) {
      for(int j=i+1;j<closeToTheLine.size();++j) {
        if (minPerim > perimeter(p, closeToTheLine[i], closeToTheLine[j])){
          minPerim = minPerim, perimeter(p, closeToTheLine[i], closeToTheLine[j]);
          // min[0] = p;
          // min[1] = closeToTheLine[i];
          // min[2] = closeToTheLine[j];
        }
      }
    }
    closeToTheLine.push_back(p);
  }

  // leftRes = searchStrip(strip, j, minPerim, leftMin);
  // if (leftRes < minPerim) {
  //   minPerim = leftRes;
  //   min[0] = leftMin[0];
  //   min[1] = leftMin[1];
  //   min[2] = leftMin[2];
  // }
  
  printf("minPerim: %f, n: %d\n", minPerim, n);
  return minPerim;
}


int main(int argc, char const *argv[])
{

  int n;
  cin >> n;
  vector<point> pointsX(n);
  vector<point> pointsY(n);
  // vector<point> min(3); 

  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    pointsX[i] = point(2*x - BIG, 2*y - BIG);
    pointsY[i] = point(2*x - BIG, 2*y - BIG);
  }

  sort(pointsX.begin(), pointsX.end(), cmpx);
  sort(pointsY.begin(), pointsY.end(), cmpy);
  
  printPoints(pointsX);

  cout << divAndConq(pointsX, pointsY, n);

  
  // cout << min[0].x << " " << min[0].y << endl;
  // cout << min[1].x << " " << min[1].y << endl;
  // cout << min[2].x << " " << min[2].y << endl;

  return 0;
}
