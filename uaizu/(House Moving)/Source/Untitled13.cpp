#include <bits/stdc++.h>
using namespace std;

using VI = vector<int>;
using VVI = vector<VI>;
using PII = pair<int, int>;
using LL = long long;
using VL = vector<LL>;
using VVL = vector<VL>;
using PLL = pair<LL, LL>;
using VS = vector<string>;

#define ALL(a)  begin((a)),end((a))
#define RALL(a) (a).rbegin(), (a).rend()
#define PB push_back
#define EB emplace_back
#define MP make_pair
#define SZ(a) int((a).size())
#define SORT(c) sort(ALL((c)))
#define RSORT(c) sort(RALL((c)))
#define UNIQ(c) (c).erase(unique(ALL((c))), end((c)))

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

#define FF first
#define SS second
template<class S, class T>
istream& operator>>(istream& is, pair<S,T>& p){
  return is >> p.FF >> p.SS;
}
template<class S, class T>
ostream& operator<<(ostream& os, const pair<S,T>& p){
  return os << p.FF << " " << p.SS;
}
template<class T>
void maxi(T& x, T y){
  if(x < y) x = y;
}
template<class T>
void mini(T& x, T y){
  if(x > y) x = y;
}


const double EPS = 1e-10;
const double PI  = acos(-1.0);
const LL MOD = 1e9+7;

class BIT{
private:
  int n;
  vector<LL> bit;
public:
  BIT(int n_){
	n = n_;
	bit.assign(n+1, 0);
  }

  LL max(int i){
	LL s = 0;
	while(i > 0){
	  maxi(s, bit[i]);
	  i -= i & -i;
	}
	return s;
  }

  void add(int i, LL x){
	while(i <= n){
	  maxi(bit[i], x);
	  i += i & -i;
	}
  }
};

int main(){
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  LL N;
  cin >> N;
  VL xs(N);
  REP(i,N) cin >> xs[i];

  BIT bit(N+1);
  LL ans = 0;
  REP(i,N){
	LL t = xs[i] + bit.max(xs[i]);
	maxi(ans, t);
	bit.add(xs[i], t);
  }
  cout << N * (N+1) / 2 - ans << endl;

  return 0;
}
