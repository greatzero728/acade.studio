#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctype.h>
#include <queue>
#include <cstring>
#include <set>
#include <bitset>
#include <map>
#include <chrono>
#include <random>
#include <unordered_map>
#include <stdio.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef std::vector<int> vi;
typedef std::vector<bool> vb;
typedef std::vector<string> vs;
typedef std::vector<double> vd;
typedef std::vector<long long> vll;
typedef std::vector<std::vector<int> > vvi;
typedef vector<vll> vvll;
typedef std::vector<std::pair<int, int> > vpi;
typedef vector<vpi> vvpi;
typedef std::pair<int, int> pi;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;

const long long mod = 1000000007;
ll gcd (ll a, ll b) {return b==0 ? a : gcd(b, a%b);}
const unsigned gen_seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937_64 gen(gen_seed);

#define all(c) (c).begin(),(c).end()
#define srt(c) sort(all(c))
#define srtrev(c) sort(all(c)); reverse(all(c))
#define forn(i, a, b) for(int i = a; i < b; i++)
#define read(x) scanf("%d", &x)
#define readv(x, n) vi x(n); forn(i,0,n) scanf("%d", &x[i])

#define pb push_back
#define mp make_pair
const int A = 100500;
int parent[A];
int rk[A];
void make_set (int v) {
    parent[v] = v;
    rk[v] = 0;
}

int find_set (int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set (parent[v]);
}

void union_sets (int a, int b) {
    a = find_set (a);
    b = find_set (b);
    if (a != b) {
        if (rk[a] < rk[b])
            swap (a, b);
        parent[b] = a;
        if (rk[a] == rk[b])
            ++rk[a];
    }
}
vvpi g;
int l;
vector<int> tin, tout;
int timer;
vector < vector<int> > up;
vvi cost;

void dfs1 (int v, int p = 0) {
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i=1; i<=l; ++i) {
        up[v][i] = up[up[v][i-1]][i-1];
        cost[v][i] = max(cost[v][i-1], cost[up[v][i-1]][i-1]);
    }
    for (size_t i=0; i<g[v].size(); ++i) {
        int to = g[v][i].first;
        if (to != p) {
            cost[to][0] = g[v][i].second;
            dfs1 (to, v);
        }
    }
    tout[v] = ++timer;
}

bool upper (int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca (int a, int b) {
    if (upper (a, b))  return a;
    if (upper (b, a))  return b;
    for (int i=l; i>=0; --i)
        if (! upper (up[a][i], b))
            a = up[a][i];
    return up[a][0];
}

int maxcost(int a, int b) {
    int ret = 0;
    int c = lca(a,b);
    for (int i=l; i>=0; --i) {
        if (! upper (up[a][i], b)) {
            ret = max(ret, cost[a][i]);
            a = up[a][i];
        }
        if (! upper (up[b][i], a)) {
            ret = max(ret, cost[b][i]);
            b = up[b][i];
        }
    }
    if(a!=c) ret = max(ret,cost[a][0]);
    if(b!=c) ret = max(ret,cost[b][0]);
    return ret;
}

int main()
{
#ifdef LOCAL
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    int n,m;
    
    read(n);
    read(m);
    forn(i,0,n) make_set(i);
    g = vvpi(n);
    ll tot = 0;
    vector<pair<int, pi>> ord;
    forn(i,0,m) {
        int v,u,c;
        scanf("%d %d %d", &u, &v, &c);
        --u;
        --v;
        ord.pb(mp(c, mp(u,v)));
    }
    srt(ord);
    for(auto x : ord) {
        int u = x.second.first;
        int v = x.second.second;
        int c = x.first;
        if(find_set(u) != find_set(v)) {
            tot+=c;
            g[u].pb(mp(v,c));
            g[v].pb(mp(u,c));
            union_sets(u, v);
        }
    }
    int nc=0;
    forn(i,0,n) if(find_set(i)==i) nc++;
    int q;
    read(q);
    if(nc > 1) {
        while(q--) {
            int u,v;
            scanf("%d %d", &u, &v);
            --u; --v;
            if(find_set(u) == find_set(v)||nc>2) printf("-1\n");
            else printf("%lld\n", tot);
        }
        exit(0);
    }
    
    
    
    
    tin.resize (n),  tout.resize (n),  up.resize (n),  cost.resize(n);
    l = 1;
    while ((1<<l) <= n)  ++l;
    for (int i=0; i<n; ++i)  up[i].resize (l+1);
    for (int i=0; i<n; ++i)  cost[i].resize (l+1);
    cost[0][0] = 0;
    dfs1 (0, 0);
    
    while(q--) {
        int u,v;
        scanf("%d %d", &u, &v);
        --u; --v;
        printf("%lld\n", tot-maxcost(u, v));
    }
    
    
    
    
    
}
