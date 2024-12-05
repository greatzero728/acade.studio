#include <iostream>
#include <algorithm>
#include <vector>
#include <complex>
#include <cmath>
using namespace std;
typedef complex<double> P;

const double eps = 1e-8;
const double pi = acos(-1);
const double inf = 1e100;

bool equals(double a, double b) {
  return abs(a-b) < eps;
}

bool equals(P a, P b) {
  return equals(a.real(),b.real()) && equals(a.imag(),b.imag());
}

namespace std {
  bool operator < (const P &a, const P b) {
    return ( a.real() != b.real()
	     ? a.real() < b.real() : a.imag() < b.imag() );
  }
}

double dot(P a, P b) {
  return a.real()*b.real() + a.imag()*b.imag();
}

double cross(P a, P b) {
  return a.real()*b.imag() - a.imag()*b.real();
}

int ccw(P p, P a, P b) {
  a -= p;
  b -= p;
  if(cross(a,b) > eps) return 1;
  if(cross(a,b) < -eps) return -1;
  if(dot(a,b) < -eps) return 2;
  if(norm(a) < norm(b)) return -2;
  return 0;
}

vector<P> convex_hull(vector<P> ps) {
  int n = ps.size(), k = 0;
  sort(ps.begin(), ps.end());
  vector<P> ch(2*n);
  for(int i = 0; i < n; ch[k++] = ps[i++])
    while(k >= 2 && ccw(ch[k-2], ch[k-1], ps[i]) <= 0) --k;
  for(int i = n-2, t = k+1; i >= 0; ch[k++] = ps[i--])
    while(k >= t && ccw(ch[k-2], ch[k-1], ps[i]) <= 0) --k;
  ch.resize(k-1);
  return ch;
}

bool isIntersect(P a1, P a2, P b1, P b2) {
  return ( ccw(a1, a2, b1) * ccw(a1, a2, b2) <= 0 &&
	   ccw(b1, b2, a1) * ccw(b1, b2, a2) <= 0 );
}

bool isIntersect(vector<P> a, vector<P> b) {
  for(int i = 0; i < a.size(); ++i) {
    for(int j = 0; j < b.size(); ++j) {
      P &a1 = a[i];
      P &a2 = a[(i+1)%a.size()];
      P &b1 = b[j];
      P &b2 = b[(j+1)%b.size()];
      if(equals(a1,b1)) continue;
      if(equals(a1,b2)) continue;
      if(equals(a2,b1)) continue;
      if(equals(a2,b2)) continue;
      if(isIntersect(a1,a2,b1,b2)) {
        return true;
      }
    }
  }
  return false;
}

double getDist(vector<P> ps) {
  double s = 0;
  for(int i = 0; i < ps.size(); ++i) {
    s += abs(ps[(i+1)%ps.size()] - ps[i]);
  }
  return s;
}


int N;
P o, D, F;
vector<P> Ps;

int main() {
  int N;
  o = P(0,0);
  while(cin >> N && N) {
    Ps.clear();
    cin >> D.real() >> D.imag();
    cin >> F.real() >> F.imag();
    for(int i = 0; i < N; ++i) {
      P p;
      cin >> p.real() >> p.imag();
      Ps.push_back(p);
    }

    if(!equals(norm(D),norm(F)) && norm(D) < norm(F)) {
      cout << -1 << endl;
      continue;
    }

    int ccwdf = ccw(o,D,F);
    if(ccwdf != 1 && ccwdf != -1) {
      printf("%.8f\n", abs(F-D));
      continue;
    }
    if(ccwdf == -1) {
      D.imag() *= -1;
      F.imag() *= -1;
      for(int i = 0; i < N; ++i) {
        Ps[i].imag() *= -1;
      }
    }
    for(int i = 0; i < Ps.size(); ++i) {
      if(!(ccw(o,D,Ps[i]) == 1 &&
           ccw(D,F,Ps[i]) == 1 &&
           ccw(F,o,Ps[i]) == 1)) {
        Ps.erase(Ps.begin()+i);
        --i;
      }
    }
    N = Ps.size();

    double ans = inf;
    for(int s = 0; s < (1<<N); ++s) {
      vector<P> q, r;
      q.push_back(o);
      q.push_back(F);
      r.push_back(D);
      r.push_back(F);
      for(int i = 0; i < N; ++i) {
        if(s & (1<<i)) {
          q.push_back(Ps[i]);
        } else {
          r.push_back(Ps[i]);
        }
      }
      double distQ;
      double distR;
      if(q.size() > 2) {
        q = convex_hull(q);
        distQ = getDist(q) - abs(F-o);
      } else {
        distQ = abs(F-o);
      }
      if(r.size() > 2) {
        r = convex_hull(r);
        distR = getDist(r) - abs(F-D);
      } else {
        distR = abs(F-D);
      }
      if(isIntersect(q,r)) continue;
      if(equals(distQ,abs(D)) || distQ < abs(D)) {
        ans = min(ans, distR);
      }
    }
    printf("%.8f\n", ans);
  }
  return 0;
}
