// Implement 35 min
// Debug1 5 min
// Debug2 5 min
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <set>

using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
static const double EPS = 1e-9;
static const double PI = acos(-1.0);

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, s, n) for (int i = (s); i < (int)(n); i++)
#define FOREQ(i, s, n) for (int i = (s); i <= (int)(n); i++)
#define FORIT(it, c) for (__typeof((c).begin())it = (c).begin(); it != (c).end(); it++)
#define MEMSET(v, h) memset((v), h, sizeof(v))

#include <complex>

typedef complex<double> Point;

struct Line : public vector<Point> {
  Line() {;}
  Line(Point a, Point b) { push_back(a); push_back(b); }
};

inline double cross(const Point &a, const Point &b) {
  return imag(conj(a) * b);
}

inline double dot(const Point &a, const Point &b) {
  return real(conj(a) * b);
}

inline int ccw(Point a, Point b, Point c) {
  b -= a;
  c -= a;
  if (cross(b, c) > 0) { return 1; }
  if (cross(b, c) < 0) { return -1; }
  //if (dot(b, c) < 0) { return 2; }
  //if (norm(b) < norm(c)) { return -2; }
  return 0;
}

bool intersectSP(const Line &s, const Point &p) {
  return abs(s[0] - p) + abs(s[1] - p) - abs(s[1] - s[0]) < EPS;
}

//================================================================

struct Event {
  double arg;
  double dist;
  int index;
  Event() {;}
  Event(double arg, double dist, int index) : arg(arg), dist(dist), index(index) {;}
  bool operator<(const Event &rhs) const {
    if (fabs(arg - rhs.arg) > EPS) { return arg > rhs.arg; }
    return dist > rhs.dist;
  }
};

int n;
double upper;
Point end;
vector<Point> kui;

bool Hit(Point from, Point to, Point center, Point p) {
  if (intersectSP(Line(from, to), p) ||
      intersectSP(Line(to, center), p) ||
      intersectSP(Line(center, from), p)) { return true; }
  int s[3];
  s[0] = ccw(p, from, to);
  s[1] = ccw(p, to, center);
  s[2] = ccw(p, center, from);
  if (s[0] * s[1] * s[2] != 0 && s[0] == s[1] && s[1] == s[2]) {
    return true;
  }
  return false;
}

bool Calc(double sum, int used, Point from, Point c, double r);
bool Move(double sum, int used, Point from, Point to, Point center, double r) {
  //cout << from << " "<< to << " " << center << " " << r << endl;
  if (r - abs(to - center) < -EPS) { return false; }
  vector<Event> es;
  REP(i, n) {
    if ((used >> i) & 1) { continue; }
    if (center != kui[i] && Hit(from, to, center, kui[i])) {
      double arg = dot(from - center, kui[i] - center) / abs(from - center) / abs(kui[i] - center);
      double dist = abs(kui[i] - center);
      es.push_back(Event(arg, dist, i));
    }
  }
  sort(es.begin(), es.end());
  if (es.empty() || kui[es[0].index] == center) {
    return Calc(sum, used, to, center, r);
  }
  used |= 1 << es[0].index;
  Point ncenter = kui[es[0].index];
  double nr = r - abs(ncenter - center);
  return Move(sum, used, from, to, ncenter, nr);
}

bool Calc(double sum, int used, Point from, Point c, double r) {
  if (sum > upper) { return true; }
  if (from == end) {
    upper = sum;
    return true;
  }
  if (sum + abs(from - end) - upper > EPS) { return false; }
  if (Move(sum + abs(from - end), used, from, end, c, r)) { return true; }
  REP(i, n) {
    if ((used >> i) & 1) { continue; }
    double nsum = sum + abs(kui[i] - from);
    if (nsum > upper) { continue; }
    Move(nsum, used | (1 << i), from, kui[i], c, r);
  }
  return false;
}

double Solve(int _n, Point s, Point e, vector<Point> _kui) {
  n = _n;
  end = e;
  kui = _kui;
  upper = abs(s) + abs(e);
  double r = abs(s);
  if (r - abs(e) < -EPS) { return -1; }
  Calc(0.0, 0, s, Point(0, 0), r);
  return upper;
}

//===================================================================

int main() {
  int n;
  double sx, sy, ex, ey;
  while (scanf("%d %lf %lf %lf %lf", &n, &sx, &sy, &ex, &ey) >= 0 && n) {
    vector<Point> kui;
    Point s(sx, sy);
    Point e(ex, ey);
    REP(i, n) {
      double x, y;
      scanf("%lf %lf", &x, &y);
      kui.push_back(Point(x, y));
    }
    random_shuffle(kui.begin(), kui.end());
    double ans = Solve(n, s, e, kui);
    if (ans == -1) {
      puts("-1");
    } else {
      printf("%.10f\n", ans);
    }
  }
}
