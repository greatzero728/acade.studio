#include <bits/stdc++.h>
using namespace std;

using P = complex<double>;

const double eps = 1e-7;

namespace std{
  template<class T> bool operator<(const complex<T> &a, const complex<T> &b) {
    return abs(a.real() - b.real()) < eps ? a.imag() + eps < b.imag() : a.real() + eps < b.real();
  }
};

double dot(P a, P b) {
  return (a * conj(b)).real();
}

double cross(P a, P b) {
  return (conj(a) * b).imag();
}

int ccw(P a, P b, P c) {
  if(cross(b-a, c-a) > eps) return 1;
  if(cross(b-a, c-a) < -eps) return -1;
  if(dot(b-a, c-a) < -eps) return -2;
  if(dot(a-b, c-b) < -eps) return 2;
  return 0;
}

bool isIntersectedSS(P a1, P a2, P b1, P b2) {
  int a = ccw(b1, b2, a1);
  int b = ccw(b1, b2, a2);
  int c = ccw(a1, a2, b1);
  int d = ccw(a1, a2, b2);

  return a * b <= 0 && c * d <= 0;
}

double distanceSP(P a, P b, P c) {
  if(dot(b-a, c-a) < eps) return abs(c-a);
  if(dot(a-b, c-b) < eps) return abs(c-b);
  return abs(cross(b-a, c-a)) / abs(b-a);
}

double getDistance(P a1, P a2, P b1, P b2) {
  if(isIntersectedSS(a1, a2, b1, b2)) return 0;

  return min({
              distanceSP(a1, a2, b1),
              distanceSP(a1, a2, b2),
              distanceSP(b1, b2, a1),
              distanceSP(b1, b2, a2),
    });
}

bool isContainedPolyP(vector<P> &g, P p) {
  int n = g.size();
  bool f = false;
  for(int i=0; i<n; i++)
    {
      P a = g[i] - p, b = g[(i+1)%n] - p;
      if (abs(cross(a, b)) < eps && dot(a, b) < eps) return true;
      if(a.imag() > b.imag()) swap(a, b);
      if(a.imag() < eps && eps < b.imag() && cross(a, b) > eps) f = !f;
    }
  return f;
}

vector<P> ConvexHull(vector<P> s) {
  int n = s.size();

  if(n < 3) return s;

  vector<P> g;
  int m;

  sort(s.begin(), s.end());

  for(int i=0; i<n; i++) {
    while((m = g.size()) >= 2 && ccw(g[m-2], g[m-1], s[i]) <= 0) g.pop_back();
    g.push_back(s[i]);
  }


  int t = g.size();

  for(int i=n-2; i>=0; i--) {
    while((m = g.size()) > t && ccw(g[m-2], g[m-1], s[i]) <= 0) g.pop_back();
    g.push_back(s[i]);
  }

  g.pop_back();


  return g;
}

bool solve() {
  int N, Dx, Dy, Fx, Fy;

  cin >> N >> Dx >> Dy >> Fx >> Fy;

  if (N == 0) return false;

  P A = P(0, 0);
  P S = P(Dx, Dy);
  P G = P(Fx, Fy);

  vector<P> vec = {A, S, G};
  vector<P> bs;

  for(int i=0; i<N; i++) {
    int x, y;
    cin >> x >> y;
    P p = P(x, y);
    if (isContainedPolyP(vec, p))
      bs.push_back(p);
  }

  N = bs.size();

  double ans = 1e17;

  for(int i=0; i<(1<<N); i++) {
    vector<P> vecA, vecB;

    for(int j=0; j<N; j++) {
      if (i & (1 << j))
        vecA.push_back(bs[j]);
      else
        vecB.push_back(bs[j]);
    }

    vecA.push_back(A);
    vecA.push_back(G);
    vecB.push_back(S);
    vecB.push_back(G);

    auto chres = ConvexHull(vecA);

    double rope = 0;

    for(int j=0; j<chres.size(); j++) {
      rope += abs(chres[j] - chres[(j+1)%chres.size()]);
    }

    rope -= abs(A - G);

    if(rope > abs(A - S) + eps) continue;

    double mov = 0;
    auto chres2 = ConvexHull(vecB);

    for(int j=0; j<chres2.size(); j++) {
      mov += abs(chres2[j] - chres2[(j+1)%chres2.size()]);
    }

    mov -= abs(S - G);

    ans = min(ans, mov);
  }


  if (ans > 1e16) {
    puts("-1");
  }else {

    printf("%.10lf\n", ans);
  }

  return true;
}

int main(){
  while(solve());
}
