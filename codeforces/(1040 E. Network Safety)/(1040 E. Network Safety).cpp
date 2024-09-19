#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
 
using namespace std;
 
const int N = 5e5+5;

int n, m, k, x, y, par[N], sz;
ll arr[N], res;
map<ll, vector<pair<int, int> > > sets;
set<int> dis;
int findP(int x){
  if(par[x] == -1) return x;
  return par[x] = findP(par[x]);
}

void join(int x, int y){
  x = findP(x);
  y = findP(y);
  if(x != y){
    par[y] = x;
    sz--;
  }
}
ll power(int b, int p){
  if(!p) return 1;
  ll res = power(b, p/2);
  if(p & 1)
    return ((res * res) % MOD) * b;
  else
    return (res * res) % MOD;
}
int main()
{
  scanf("%d %d %d", &n, &m, &k);
  for(int i=0; i<n; i++)
    scanf("%lld", arr+i);
  for(int i=0; i<m; i++){
    scanf("%d %d", &x, &y);
    x--, y--;
    ll idx = arr[x] ^ arr[y];
    sets[idx].push_back({x, y});
  }
    res = 0;
  memset(par, -1, sizeof par);
  for(auto a: sets){
    vector<pair<int, int> > tmp = a.second;
    sz = n;
    for(auto x: tmp){
      dis.insert(x.first);
      dis.insert(x.second);
      join(x.first, x.second);
    }
    res = (res + power(2, sz)) % MOD;
    while(dis.size()){
      int tmp = *(dis.begin());
      par[tmp] = -1;
      dis.erase(dis.begin());
    }
  }
  res = ((((1LL << k) - sets.size()) % MOD * power(2, n)) % MOD + res) % MOD;
  cout << res << endl;

  return 0;
}
