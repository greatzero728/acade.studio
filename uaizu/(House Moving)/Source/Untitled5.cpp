#include <queue>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <set>

#define REP(i,n) for(int i=0; i<(int)(n); i++)

typedef long long ll;

inline int getInt(){ int s; scanf("%d", &s); return s; }

using namespace std;

class BIT{
  vector<ll> bit;
public:
  BIT(int n) : bit(n + 1) {}
  void update(int idx, ll val){
    idx++;
    while(idx < (int)bit.size()){
      bit[idx] = max(bit[idx], val);
      idx += idx & -idx;
    }
  }

  ll p(int i){
    ll s = 0;
    i++;
    while(i > 0){
      s = max(s, bit[i]);
      i -= i & -i;
    }
    return s;
  }
};

int main(){
  const int n = getInt();
  BIT bit(n + 1);

  REP(i,n){
    const int x = getInt();
    bit.update(x, bit.p(x) + x);
  }

  printf("%lld\n", (ll)n * (ll)(n + 1) / 2 - bit.p(n));

  return 0;
}