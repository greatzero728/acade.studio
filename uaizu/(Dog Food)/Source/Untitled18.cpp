#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <complex>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <climits>
#include <queue>
#include <set>
#include <map>
#include <valarray>
#include <bitset>
#include <stack>
using namespace std;

#define REP(i,n) for(int i=0;i<(int)n;++i)
#define FOR(i,c) for(__typeof((c).begin())i=(c).begin();i!=(c).end();++i)
#define ALL(c) (c).begin(), (c).end()
typedef long long ll;
typedef pair<int,int> pii;
const int INF = 1<<29;
const double PI = acos(-1);
const double EPS = 1e-8;

typedef complex<double> P;
namespace std {
  bool operator < (const P& a, const P& b) {
    // if (abs(a-b)<EPS) return 0;
    return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
  }
}
double cross(const P& a, const P& b) {
  return imag(conj(a)*b);
}
double dot(const P& a, const P& b) {
  return real(conj(a)*b);
}
struct L : public vector<P> {
  L(const P &a, const P &b) {
    push_back(a); push_back(b);
  }
  L() {}
};
int ccw(P a, P b, P c) {
  b -= a; c -= a;
  if (cross(b, c) > 0)   return +1;       // counter clockwise
  if (cross(b, c) < 0)   return -1;       // clockwise
  if (dot(b, c) < 0)     return +2;       // c--a--b on line
  if (norm(b) < norm(c)) return -2;       // a--b--c on line
  return 0;
}
typedef vector<P> G;
#define curr(P, i) P[i]
#define next(P, i) P[(i+1)%P.size()]
// ?-????????
bool convex_contain(const G &g, const P &p) { // ????????
  REP(i,g.size())
    if (ccw(g[i], next(g, i), p) == -1) return 0;
  return 1;
}
// ????
double angle(const P &a, const P &b) {        // ????a????????b??????[0,2pi]
  double ret = arg(b)-arg(a);
  return (ret>=0) ? ret : ret + 2*PI;
}
double angle2(const P &a, const P &b) { // ????a?????b?????
  return min(angle(a,b), angle(b,a));
}
P rotate(P p, double ang) {
  return p * P(cos(ang), sin(ang));
}


P p[10];
P dog;
int n;

typedef pair<double,double> pdd;
// center??????????d??p[nxt]??????????????????
pdd func(int &center, const P &d, int nxt) {
  //cout << "func(" << p[center] << ", " << d << ", " << p[nxt] << ")" << endl;
  L l(d, p[nxt]);
  int cw = ccw(p[center], d, p[nxt]);
  if (abs(cw) != 1) {           // ikeru
    return pdd(0, abs(p[nxt]-d));
  }
  G g(3);
  g[0] = p[center];
  g[1] = d;
  g[2] = p[nxt];
  if (cw == -1) swap(g[1],g[2]);
  double minang = INF;
  int id = -1;
  REP(i,n+1) {
    if (convex_contain(g, p[i])) {
      if (i == nxt || i == center || abs(p[i]-d) < EPS) continue;
      double ang = angle2(d-p[center], p[i]-p[center]);
      if (minang > ang){
        minang = ang;
        id = i;
      }
    }
  }
  if (id == -1) {
    // ikeru
    return pdd(0, abs(p[nxt]-d));
  }
  pdd res = pdd(abs(p[id]-p[center]), 0);
  center = id;
  pdd ret = func(center, d, nxt);
  return pdd(res.first + ret.first, res.second + ret.second);
}

double ans;

double simulate(vector<int> v) {
  double sum = 0;
  int center = n;
  P now = dog;
  double res = 0;
  v.push_back(9);
  REP(i,v.size()) {
    pdd ret = func(center, now, v[i]);
    sum += ret.first;
    res += ret.second;
    // cout << sum << " " << res << endl;
    now = p[v[i]];
    if (sum+abs(p[center]-p[9]) > abs(dog) + EPS) return INF;
    if (res > ans) return INF;
  }
  sum += abs(p[center] - now);
  // FOR(it, v) cout << *it << " ";cout << endl;
  // cout << sum << ", " << res << endl;
  if (sum > abs(dog)+EPS) return INF;
  // if (res < 220) {
  //   FOR(it, v) cout << *it << " "; cout << endl;
  //   cout << p[center] << " " << now << endl;
  //   cout << sum << " " << res << endl;
  // }
  else return res;
}

vector<int> v;
void solve(int S) {
  ans = min(ans, simulate(v));
  if (S==(1<<n)-1) return;
  REP(i,n) {
    if (!(S>>i&1)) {
      v.push_back(i);
      solve(S|1<<i);
      v.pop_back();
    }
  }
}

int main() {
  while(cin>>n,n) {
    cin >> dog.real() >> dog.imag();
    cin >> p[9].real() >> p[9].imag();
    REP(i,n) cin >> p[i].real() >> p[i].imag();
    p[n] = P(0,0);
    // vector<int> v(2);v[0]=0;v[1]=5;
    // simulate(v);return 0;
    ans = simulate(vector<int>(1,n));
    solve(0);
    if (ans >= INF-EPS) {
      cout << -1 << endl;
    } else {
      printf("%.10f\n", ans);
    }
  }
}
