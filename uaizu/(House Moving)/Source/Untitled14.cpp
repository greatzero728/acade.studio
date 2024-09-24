#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#define REP(i,s,n) for(int i=(int)(s);i<(int)(n);i++)
#define DEBUGP(val) cerr << #val << "=" << val << "\n"

using namespace std;
typedef long long int ll;
typedef vector<int> VI;
typedef vector<ll> VL;
typedef pair<int, int> PI;

/**
 * I should implement static I op(I, I).
 */
template<class I>
class SegTree {
  int n;
  std::vector<I> dat;
  I e;
public:
  SegTree(int n_, I e) : e(e) {
    n = 1;
    while (n < n_) { n *= 2; } // n is a power of 2
    dat.resize(2 * n);
    for (int i = 0; i < 2 * n - 1; i++) {
      dat[i] = e;
    }
  }
  /* ary[k] <- v */
  void update(int k, I v) {
    k += n - 1;
    dat[k] = v;
    while (k > 0) {
      k = (k - 1) / 2;
      dat[k] = I::op(dat[2 * k + 1], dat[2 * k + 2]);
    }
  }
  /* http://proc-cpuinfo.fixstars.com/2017/07/optimize-segment-tree/ */
  I query(int a, int b) const {
    I left = e;
    I right = e;
    a += n - 1;
    b += n - 1;
    while (a < b) {
      if ((a & 1) == 0) {
	left = I::op(left, dat[a]);
      }
      if ((b & 1) == 0) {
	right = I::op(dat[b - 1], right);
      }
      a = a / 2;
      b = (b - 1) / 2;
    }
    return I::op(left, right);
  }
};

struct max_ll {
  ll v;
  max_ll(): v(0) {}
  max_ll(ll v): v(v) {}
  operator ll() const { return v; }
  static max_ll op(max_ll x, max_ll y) {
    return std::max(x, y);
  }
};

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  scanf("%d", &n);
  std::vector<int> x(n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &x[i]);
  auto seg =
    SegTree<max_ll>(n + 1, std::numeric_limits<ll>::min());
  ll ma = 0;
  for (int i = 0; i < n; ++i) {
    ll res = std::max((ll)seg.query(1, x[i]), 0LL);
    ll cur = res + x[i];
    ma = std::max(ma, cur);
    seg.update(x[i], cur);
  }
  ll whole = (ll)n * (ll)(n + 1) / 2;
  printf("%lld\n", whole - ma);
}
