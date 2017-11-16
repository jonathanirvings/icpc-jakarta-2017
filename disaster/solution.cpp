// Solution by Vincentius Madya P. I.

// INCLUDE LIST
#include <cstdio>
#include <bitset>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
#include <list>
#include <vector>
#include <cstdlib>
#include <cctype>
#include <cmath>
using namespace std;

vector<int> pset;
void initSet(int _size) {
  pset.resize(_size);
  for (int i = 0; i < pset.size(); i++)
    pset[i] = i;
}
int findSet(int i) { return (pset[i] == i) ? i : (pset[i] = findSet(pset[i])); }
void unionSet(int i, int j) { pset[findSet(i)] = findSet(j); }
bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

/*
  Based on http://home.iitk.ac.in/~sshekh/codes/notebook.html#file8
*/
double INF = 1e100;
double EPS = 1e-9;

struct PT {
  double x, y;
  PT() {}
  PT(double x, double y) : x(x), y(y) {}
  PT(pair<double, double> p) : x(p.first), y(p.second) {}
  PT(const PT &p) : x(p.x), y(p.y)    {}
  PT operator + (const PT &p)  const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p)  const { return PT(x-p.x, y-p.y); }
  PT operator * (double c)     const { return PT(x*c,   y*c  ); }
  PT operator / (double c)     const { return PT(x/c,   y/c  ); }
};

bool isEqual(double lhs, double rhs) {
  return (fabs(lhs - rhs) < EPS);
}

double dot(PT p, PT q) { return p.x * q.x + p.y * q.y; }
double dist2(PT p, PT q) { return dot(p - q,p - q); }

PT RotateCCW90(PT p) { return PT(-p.y, p.x); }

struct GeoObject {
  bool isLine;

  PT p1, p2;
  double r;

  // Constructor
  GeoObject(PT _p1, PT _p2) {
    p1 = _p1;
    p2 = _p2;
    isLine = true;
  }

  GeoObject(PT _center, double _radius) {
    p1 = _center;
    r = _radius;
    isLine = false;
  }
};

// Global Variable
vector<GeoObject> objects;

// compute intersection of line through points a and b with
// circle centered at c with radius r > 0
vector<pair<double, double> > CircleLineIntersection(PT a, PT b, PT c, double r) {
  vector<PT> ret;
  vector<pair<double, double> > result;
  b = b-a;
  a = a-c;
  double A = dot(b, b);
  double B = dot(a, b);
  double C = dot(a, a) - r * r;
  double D = B * B - A * C;
  if (D < 0.0) return result;
  ret.push_back(c + a + b * (-B + sqrt(D)) / A);
  if (D > 0.0)
    ret.push_back(c + a + b * (-B - sqrt(D)) / A);

  for (int i = 0; i < ret.size(); i++) {
    result.push_back(make_pair(ret[i].x, ret[i].y));
  }
  return result;
}

// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
// Based on : http://cs.stanford.edu/group/acm/SLPC/notebook.pdf
vector<PT> CircleCircleIntersection(PT a, PT b, double r, double R) {
  vector<PT> ret;
  double d = sqrt(dist2(a, b));
  if (d > r + R || d + min(r, R) < max(r, R))
    return ret;
  double x = (d * d - R * R + r * r) / (2 * d);
  double y = sqrt(r * r - x * x);
  PT v = (b - a) / d;
  ret.push_back(a + v * x + RotateCCW90(v) * y);
  if (y > 0)
    ret.push_back(a + v * x - RotateCCW90(v) * y);
  return ret;
}

double X1, Y1, X2, Y2;
bool insideSquare(PT a) {
  return (a.x - EPS > X1 && a.x < X2 - EPS && a.y - EPS > Y1 && a.y < Y2 - EPS);
}

bool insideBorderSquare(PT a) {
  if (isEqual(a.y, Y1) || isEqual(a.y, Y2)) {
    return a.x - EPS > X1 && a.x < X2 - EPS;
  }

  if (isEqual(a.x, X2) || isEqual(a.x, X1)) {
    return a.y - EPS > Y1 && a.y < Y2 - EPS;
  }

  return insideSquare(a);
}

bool inCorner(PT a) {
  return (isEqual(a.y, Y1) || isEqual(a.y, Y2)) && (isEqual(a.x, X2) || isEqual(a.x, X1));
}

void solve() {
  double _x1, _y1, _x2, _y2;
  double x, y, r;
  int n;

  cin >> _x1 >> _y1 >> _x2 >> _y2 >> n;
  X1 = _x1;
  X2 = _x2;
  Y1 = _y1;
  Y2 = _y2;

  // Fill vector with lines
  /*
             2
    (X1, Y2) - - - (X2, Y2)
      |              |
      |              |
   3  |              |  1
      |              |
      |              |
    (X1, Y1) - - - (X2, Y1)
             0
  */
  objects.push_back(GeoObject(PT(_x1, _y1), PT(_x2, _y1)));
  objects.push_back(GeoObject(PT(_x2, _y1), PT(_x2, _y2)));
  objects.push_back(GeoObject(PT(_x2, _y2), PT(_x1, _y2)));
  objects.push_back(GeoObject(PT(_x1, _y2), PT(_x1, _y1)));

  for (int i = 0; i < n; i++) {
    cin >> x >> y >> r;
    objects.push_back(GeoObject(PT(x, y), r));
  }

  initSet(10000);
  // Check line to circle intersection
  for (int i = 0; i < 4; i++) {
    for (int j = 4; j < objects.size(); j++) {
      if (dist2(objects[i].p1, objects[j].p1) <= objects[j].r * objects[j].r && dist2(objects[i].p2, objects[j].p1) <= objects[j].r * objects[j].r) {
        unionSet(i, j);
        continue;
      }

      if (dist2(objects[i].p1, objects[j].p1) < objects[j].r * objects[j].r || dist2(objects[i].p2, objects[j].p1) < objects[j].r * objects[j].r) {
        unionSet(i, j);
        continue;
      }

      vector<pair<double, double> > res = CircleLineIntersection(objects[i].p1, objects[i].p2, objects[j].p1, objects[j].r);
      if (res.size() == 2) {
        if (insideBorderSquare(PT(res[0])) || insideBorderSquare(PT(res[1]))) {
          unionSet(i, j);
        }
      }
    }
  }

  // Check circle to circle intersection
  for (int i = 4; i < objects.size(); i++) {
    for (int j = 4; j < objects.size(); j++) {
      vector<PT> res = CircleCircleIntersection(objects[i].p1, objects[j].p1, objects[i].r, objects[j].r);
      if (res.size() == 2) {
        if (insideBorderSquare(res[0]) || insideBorderSquare(res[1]) || (inCorner(res[0]) && inCorner(res[1]))) {
          unionSet(i, j);
        }
      }
    }
  }

  // Check possible way
  bool can = true;
  can &= !isSameSet(3, 0);
  can &= !isSameSet(3, 1);
  can &= !isSameSet(2, 0);
  can &= !isSameSet(2, 1);

  if (can) cout << "YES" << endl;
  else cout << "NO" << endl;
}

int main() {
  solve();
  return 0;
}
