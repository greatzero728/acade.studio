#include <bits/stdc++.h>
//#include <atcoder/all>
//using namespace atcoder;
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
 
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef pair<int, int> pii;
typedef pair<long long, long long> PLL;
typedef pair<int, PII> TIII;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
 
#define FOR(i, s, n) for (int i = s; i < (int)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) x.begin(), x.end()
 
#define MOD 1000000007
 
template<class T1, class T2> inline bool chmax(T1 &a, T2 b) {if (a < b) {a = b; return true;} return false;}
template<class T1, class T2> inline bool chmin(T1 &a, T2 b) {if (a > b) {a = b; return true;} return false;}
const double EPS = 1e-8, PI = acos(-1);
const double pi = 3.141592653589793238462643383279;
//??????    
typedef string::const_iterator State;
ll GCD(ll a, ll b){
  return (b==0)?a:GCD(b, a%b);
}
ll LCM(ll a, ll b){
  return a/GCD(a, b) * b;
}
template< int mod >
struct ModInt {
  int x;
 
  ModInt() : x(0) {}
 
  ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
 
  ModInt &operator+=(const ModInt &p) {
    if((x += p.x) >= mod) x -= mod;
    return *this;
  }
 
  ModInt &operator-=(const ModInt &p) {
    if((x += mod - p.x) >= mod) x -= mod;
    return *this;
  }
 
  ModInt &operator*=(const ModInt &p) {
    x = (int) (1LL * x * p.x % mod);
    return *this;
  }
 
  ModInt &operator/=(const ModInt &p) {
    *this *= p.inverse();
    return *this;
  }
 
  ModInt operator-() const { return ModInt(-x); }
 
  ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
 
  ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
 
  ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
 
  ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
 
  bool operator==(const ModInt &p) const { return x == p.x; }
 
  bool operator!=(const ModInt &p) const { return x != p.x; }
 
  ModInt inverse() const {
    int a = x, b = mod, u = 1, v = 0, t;
    while(b > 0) {
      t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    return ModInt(u);
  }
 
  ModInt pow(int64_t n) const {
    ModInt ret(1), mul(x);
    while(n > 0) {
      if(n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }
 
  friend ostream &operator<<(ostream &os, const ModInt &p) {
    return os << p.x;
  }
 
  friend istream &operator>>(istream &is, ModInt &a) {
    int64_t t;
    is >> t;
    a = ModInt< mod >(t);
    return (is);
  }
 
  static int get_mod() { return mod; }
};
 
using modint = ModInt< 1000000007 >;
template< typename T >
struct Combination {
  vector< T > _fact, _rfact, _inv;
 
  Combination(int sz) : _fact(sz + 1), _rfact(sz + 1), _inv(sz + 1) {
    _fact[0] = _rfact[sz] = _inv[0] = 1;
    for(int i = 1; i <= sz; i++) _fact[i] = _fact[i - 1] * i;
    _rfact[sz] /= _fact[sz];
    for(int i = sz - 1; i >= 0; i--) _rfact[i] = _rfact[i + 1] * (i + 1);
    for(int i = 1; i <= sz; i++) _inv[i] = _rfact[i] * _fact[i - 1];
  }
 
  inline T fact(int k) const { return _fact[k]; }
 
  inline T rfact(int k) const { return _rfact[k]; }
 
  inline T inv(int k) const { return _inv[k]; }
 
  T P(int n, int r) const {
    if(r < 0 || n < r) return 0;
    return fact(n) * rfact(n - r);
  }
 
  T C(int p, int q) const {
    if(q < 0 || p < q) return 0;
    return fact(p) * rfact(q) * rfact(p - q);
  }
 
  T H(int n, int r) const {
    if(n < 0 || r < 0) return (0);
    return r == 0 ? 1 : C(n + r - 1, r);
  }
};
 
ll modpow(ll x, ll n, ll mod) {
  ll res = 1;
  x %= mod;
  if(x == 0) return 0;
  while(n) {
    if(n&1) res = (res * x) % mod;
    x = (x * x) % mod;
    n >>= 1;
  }
  return res;
} 
inline long long mod(long long a, long long m) {
    return (a % m + m) % m;
}
template<typename T> 
struct BIT{
  int N;
  std::vector<T> node;
  BIT(){}
  BIT(int n){
    N = n;
    node.resize(N+10);
  }
  void build(int n) {
    N = n;
    node.resize(N+10);
  }
  /* a: 1-indexed */
  void update(int a, T x){
    for(int i=a; i<(int)node.size(); i += i & -i) node[i] = max(node[i],x);
  }

  /* [1, a] */
  T query(int a){
    T res = 0;
    for(int x=a; x>0; x -= x & -x) res = max(res,node[x]);
    return res;
  }


  /* 
    a1+a2+...+aw >= val?????????w???
    @verify https://codeforces.com/contest/992/problem/E
  */
  int lower_bound(T val) {
    if(val < 0) return 0;

    int res = 0;
    int n = 1; 
    while (n < N) n *= 2;

    T tv=0;
    for (int k = n; k > 0; k /= 2) {
      if(res + k < N && node[res + k] < val){
        val -= node[res+k];
        res += k;
      }
    }
    return res+1; 
  }
};
struct UnionFind{
  std::vector<int> par;
  std::vector<int> siz;

  UnionFind(int sz_): par(sz_), siz(sz_) {
    for(int i=0; i<sz_; ++i) par[i] = i, siz[i] = 1;
  }

  void init(int sz_){
    par.resize(sz_);
    siz.resize(sz_);
    for(int i=0; i<sz_; ++i) par[i] = i, siz[i] = 1;
  }

  int root(int x){
    if(x == par[x]) return x;
    return par[x] = root(par[x]);
  }

  bool merge(int x, int y){
    x = root(x), y = root(y);
    if(x == y) return false;
    if(siz[x] < siz[y]) std::swap(x, y);
    siz[x] += siz[y];
    par[y] = x;
    return true;
  }

  bool issame(int x, int y){
    return root(x) == root(y);
  }

  int size(int x){
    return siz[root(x)];
  }
};
struct RollingHash{

    using ull = unsigned long long;
    const ull mod = (1ULL << 61) - 1;
    const ull MASK30 = (1ULL << 30) - 1;
    const ull MASK31 = (1ULL << 31) - 1;

    const ull MASK61 = mod;

    ull base;
    int n;
    vector<ull> hash, pow;

    RollingHash(const string &s)
    {
        random_device rnd;
        mt19937_64 mt(rnd());
        base = calc_mod(mt()) % 100000 + 1000;
        
        n = (int)s.size();
        hash.assign(n+1, 0);
        pow.assign(n+1, 1);
        
        for(int i=0; i<n; i++){
            hash[i+1] = calc_mod(mul(hash[i], base) + s[i]);
            pow[i+1] = calc_mod(mul(pow[i], base));
        }
    }

    ull calc_mod(ull x){
        ull xu = x >> 61;
        ull xd = x & MASK61;
        ull res = xu + xd;
        if(res >= mod) res -= mod;
        return res;
    }

    ull mul(ull a, ull b){
        ull au = a >> 31;
        ull ad = a & MASK31;
        ull bu = b >> 31;
        ull bd = b & MASK31;
        ull mid = ad * bu + au * bd;
        ull midu = mid >> 30;
        ull midd = mid & MASK30;
        return calc_mod(au * bu * 2 + midu + (midd << 31) + ad * bd);
    }

    //[l,r)??????
    inline ull get(int l, int r){
        ull res = calc_mod(hash[r] + mod*3-mul(hash[l], pow[r-l]));
        return res;
    }
    //string t??????
    inline ull get(string t){
        ull res = 0;
        for(int i=0; i<t.size(); i++){
            res = calc_mod(mul(res, base)+t[i]);
        }
        return res;
    }
    //string s??t???????
    inline int count(string t) {
        if(t.size() > n) return 0;
        auto hs = get(t);
        int res = 0;
        for(int i=0; i<n-t.size()+1; i++){
            if(get(i, i+t.size()) == hs) res++; 
        }
        return res;
    }

    /* 
        concat 
        @verify https://codeforces.com/problemset/problem/514/C
    */
    inline ull concat(ull h1, ull h2, int h2len){
      return calc_mod(h2 + mul(h1, pow[h2len]));
    }

    // LCP???? S[a:] T[b:]
    inline int LCP(int a, int b){
        int len = min((int)hash.size()-a, (int)hash.size()-b);
        
        int lb = -1, ub = len;
        while(ub-lb>1){
            int mid = (lb+ub)/2;

            if(get(a, a+mid) == get(b, b+mid)) lb = mid;
            else ub = mid;
        }
        return lb;
    }
};

int main() {  
  cin.tie(0);
  ios::sync_with_stdio(false);
  cout << fixed << setprecision(12);
 
  int n; cin >> n;
  BIT<ll> bit(n+1);
  vector<int> a(n);
  ll ans = 0;
  REP(i,n) {
    cin >> a[i];
    ll q = bit.query(a[i]-1);
    ans = max(ans, q + a[i]);
    bit.update(a[i], q+a[i]);
  }
  cout << 1LL * n * (n+1) / 2 - ans << endl;
  return 0;
}