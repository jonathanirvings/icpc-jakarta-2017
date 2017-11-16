// Second solution by Jonathan Irvin Gunawan

// 00.32.29

#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef long double Double;
typedef pair<Double, Double> point;

const Double EPS = 1e-9;

bool smaller(Double a, Double b) {
  return a + EPS < b;
}

bool equals(Double a, Double b) {
  return fabs(a - b) < EPS;
}

bool smallerequals(Double a, Double b) {
  return smaller(a, b) || equals(a, b);
}

Double square(Double a) {
  return a * a;
}

Double distance(point a, point b) {
  return sqrt(square(b.x - a.x) + square(b.y - a.y));
}

point get_point(point a, point b, Double d) {
  if (equals(a.x, b.x) && equals(a.y, b.y)) {
    return a;
  }
  Double ratio = d / distance(a, b);
  Double x = a.x + (b.x - a.x) * ratio;
  Double y = a.y + (b.y - a.y) * ratio;
  return make_pair(x, y);
}

vector<point> find_intersections(point p_a, Double r_a, point p_b, Double r_b) {
  Double p_dist = distance(p_a, p_b);
  if (smaller(r_a + r_b, p_dist)) {
    return {};
  }
  if (equals(r_a + r_b, p_dist)) {
    return {get_point(p_a, p_b, r_a)};
  } else {
    point p_1 = get_point(p_a, p_b, p_dist - r_b);
    point p_2 = get_point(p_b, p_a, p_dist - r_a);
    point p_0 = make_pair((p_1.x + p_2.x) / 2, (p_1.y + p_2.y) / 2);
    Double h = sqrt(square(r_a) - square(distance(p_a, p_0)));

    return {make_pair(p_0.x + h * (p_b.y - p_a.y) / p_dist,
                      p_0.y - h * (p_b.x - p_a.x) / p_dist),
            make_pair(p_0.x - h * (p_b.y - p_a.y) / p_dist,
                      p_0.y + h * (p_b.x - p_a.x) / p_dist)};
  }
}

vector<Double> find_y_intersections(point p, Double r, Double x) {
  if (smaller(square(r) - square(x - p.x), 0)) {
    return {};
  }
  if (equals(square(r) - square(x - p.x), 0)) {
    return {sqrt(square(r) - square(x - p.x)) + p.y};
  }
  return {-sqrt(square(r) - square(x - p.x)) + p.y,
          sqrt(square(r) - square(x - p.x)) + p.y};
}

vector<Double> find_x_intersections(point p, Double r, Double y) {
  if (smaller(square(r) - square(y - p.y), 0)) {
    return {};
  }
  if (equals(square(r) - square(y - p.y), 0)) {
    return {sqrt(square(r) - square(y - p.y)) + p.x};
  }
  return {-sqrt(square(r) - square(y - p.y)) + p.x,
          sqrt(square(r) - square(y - p.y)) + p.x};
}

bool is_start(point p, Double r, point one, point two) {
  vector<Double> y_intersections = find_y_intersections(p, r, one.x);
  if (y_intersections.size() > 1) {
    for (Double y : y_intersections) {
      if (smaller(one.y, y) && smaller(y, two.y)) {
        return true;
      }
    }
    if (smallerequals(one.y, y_intersections[0])
        && smaller(y_intersections[0], two.y)) {
      return true;
    }
    if (smaller(one.y, y_intersections[1])
        && smallerequals(y_intersections[1], two.y)) {
      return true;
    }
  }
  vector<Double> x_intersections = find_x_intersections(p, r, two.y);
  if (x_intersections.size() > 1) {
    for (Double x : x_intersections) {
      if (smaller(one.x, x) && smaller(x, two.x)) {
        return true;
      }
    }
    if (smallerequals(one.x, x_intersections[0])
        && smaller(x_intersections[0], two.x)) {
      return true;
    }
    if (smaller(one.x, x_intersections[1])
        && smallerequals(x_intersections[1], two.x)) {
      return true;
    }
  }
  return false;
}

bool is_end(point p, Double r, point one, point two) {
  vector<Double> y_intersections = find_y_intersections(p, r, two.x);
  if (y_intersections.size() > 1) {
    for (Double y : y_intersections) {
      if (smaller(one.y, y) && smaller(y, two.y)) {
        return true;
      }
    }
    if (smallerequals(one.y, y_intersections[0])
        && smaller(y_intersections[0], two.y)) {
      return true;
    }
    if (smaller(one.y, y_intersections[1])
        && smallerequals(y_intersections[1], two.y)) {
      return true;
    }
  }
  vector<Double> x_intersections = find_x_intersections(p, r, one.y);
  if (x_intersections.size() > 1) {
    for (Double x : x_intersections) {
      if (smaller(one.x, x) && smaller(x, two.x)) {
        return true;
      }
    }
    if (smallerequals(one.x, x_intersections[0])
        && smaller(x_intersections[0], two.x)) {
      return true;
    }
    if (smaller(one.x, x_intersections[1])
        && smallerequals(x_intersections[1], two.x)) {
      return true;
    }
  }
  return false;
}

bool canReachGoal(int N,
                  point one,
                  point two,
                  vector<point> points,
                  vector<Double> radius) {
  vector<vector<int>> adj(N);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (i != j) {
        vector<point> intersections = find_intersections(points[i],
                                                         radius[i],
                                                         points[j],
                                                         radius[j]);
        bool valid_intersection = false;
        if (intersections.size() < 2) {
          continue;
        }
        for (point p : intersections) {
          if (smallerequals(p.x, one.x) || smallerequals(two.x, p.x)
              || smallerequals(p.y, one.y) || smallerequals(two.y, p.y)) {
          } else {
            valid_intersection = true;
          }
        }
        int number_of_intersections_inside_or_line = 0;
        for (point p : intersections) {
          if (smaller(p.x, one.x) || smaller(two.x, p.x)
              || smaller(p.y, one.y) || smaller(two.y, p.y)) {
          } else {
            ++number_of_intersections_inside_or_line;
          }
        }
        if (valid_intersection || number_of_intersections_inside_or_line == 2) {
          adj[i].push_back(j);
        }
      }
    }
  }
  vector<int> start, finish;
  for (int i = 0; i < N; ++i) {
    if (is_start(points[i], radius[i], one, two)) {
      start.push_back(i);
    }
    if (is_end(points[i], radius[i], one, two)) {
      finish.push_back(i);
    }
  }
  if (false) {
    for (int i : start) printf("%d ", i); puts("<<< START");
    for (int i : finish) printf("%d ", i); puts("<<< FINISH");
    for (int i = 0; i < N; ++i) {
      for (int j : adj[i]) printf("%d ", j);
      printf("<<<< %d\n", i);
    }
  }
  queue<int> q;
  for (int i : start) {
    q.push(i);
  }
  vector<bool> visited(N);
  while (!q.empty()) {
    int now = q.front();
    q.pop();
    if (visited[now]) {
      continue;
    }
    visited[now] = true;
    for (int i : adj[now]) {
      q.push(i);
    }
  }
  for (int i : finish) {
    if (visited[i]) {
      return false;
    }
  }
  return true;
}

int main() {
  assert(canReachGoal(5, make_pair(-15, -10), make_pair(15, 10),
         {make_pair(-20, 7),
          make_pair(-2, 3),
          make_pair(8, -3),
          make_pair(-1, -8),
          make_pair(-9, -1)},
         {9, 6, 4, 3, 3}));
  assert(!canReachGoal(3, make_pair(2, 10), make_pair(18, 30),
         {make_pair(10, 20),
          make_pair(10, 29),
          make_pair(10, 11)},
         {5, 5, 5}));
  assert(canReachGoal(3, make_pair(2, 10), make_pair(18, 30),
         {make_pair(10, 20),
          make_pair(10, 25),
          make_pair(10, 10)},
         {5, 5, 5}));
  assert(canReachGoal(3, make_pair(2, 10), make_pair(18, 30),
         {make_pair(10, 19),
          make_pair(10, 25),
          make_pair(10, 10)},
         {5, 5, 5}));
  assert(!canReachGoal(3, make_pair(2, 10), make_pair(18, 30),
         {make_pair(10, 19),
          make_pair(10, 26),
          make_pair(10, 10)},
         {5, 5, 5}));
  assert(!canReachGoal(2, make_pair(0, 0), make_pair(1.9, 3),
         {make_pair(0, 1.5),
          make_pair(1.9, 1.5)},
         {1.5, 1.5}));
  assert(canReachGoal(2, make_pair(0, 0), make_pair(3, 3),
         {make_pair(0, 1.5),
          make_pair(3, 1.5)},
         {1.5, 1.5}));
  assert(!canReachGoal(2, make_pair(0, 0), make_pair(2.9, 3),
         {make_pair(0, 1.5),
          make_pair(2.9, 1.5)},
         {1.5, 1.5}));
  assert(!canReachGoal(7, make_pair(0, 0), make_pair(10, 10),
         {make_pair(-1, -1),
          make_pair(-1, 0),
          make_pair(-1, 1),
          make_pair(0, -1),
          make_pair(0, 1),
          make_pair(1, -1),
          make_pair(1, 0)},
         {1, 1, 1, 1, 1, 1, 1}));
  assert(canReachGoal(7, make_pair(0, 0), make_pair(10, 10),
         {make_pair(-1, -1),
          make_pair(-1, 0),
          make_pair(-1, 1),
          make_pair(0, -1),
          make_pair(0, 1),
          make_pair(1, -1),
          make_pair(1, 0)},
         {0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6}));
  assert(!canReachGoal(8, make_pair(0, 0), make_pair(10, 10),
         {make_pair(-1, -1),
          make_pair(-1, 0),
          make_pair(-1, 1),
          make_pair(0, -1),
          make_pair(0, 1),
          make_pair(1, -1),
          make_pair(1, 0),
          make_pair(1, 1)},
         {0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6}));
  assert(canReachGoal(1, make_pair(0, 0), make_pair(10, 10),
         {make_pair(-3, -4)},
         {5}));
  assert(canReachGoal(1, make_pair(0, 0), make_pair(10, 10),
         {make_pair(5, 5)},
         {5}));
  assert(!canReachGoal(1, make_pair(0, 0), make_pair(10, 10),
         {make_pair(5, 5)},
         {5.1}));
  assert(canReachGoal(1, make_pair(0, 0), make_pair(10, 10),
         {make_pair(9, 10)},
         {1}));
  assert(!canReachGoal(1, make_pair(0, 0), make_pair(7, 7),
         {make_pair(3, 4)},
         {5}));
  assert(canReachGoal(1, make_pair(0, 0), make_pair(10, 10),
         {make_pair(13, 14)},
         {5}));
  assert(canReachGoal(2, make_pair(10, 10), make_pair(20, 20),
         {make_pair(17, 24), make_pair(24, 17)},
         {5, 5}));
  int N;
  point one, two;
  scanf("%Lf %Lf %Lf %Lf %d", &one.x, &one.y, &two.x, &two.y, &N);
  vector<point> points(N);
  vector<Double> radius(N);
  for (int i = 0; i < N; ++i) {
    scanf("%Lf %Lf %Lf", &points[i].x, &points[i].y, &radius[i]);
  }
  puts(canReachGoal(N, one, two, points, radius) ? "YES" : "NO");
}
