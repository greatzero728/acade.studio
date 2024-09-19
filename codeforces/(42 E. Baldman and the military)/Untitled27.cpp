
#include <bits/stdc++.h>

using namespace std;

//#define MULTITEST

#define x first
#define y second
#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define sz(a) int(a.size())
#define all(a) a.begin(), a.end()
#define forn(i, n) for(int i = 0; i < int(n); i++) 
#define fore(i, l, r) for(int i = int(l); i < int(r); i++)

typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;

template <class A, class B> ostream& operator << (ostream& out, const pair<A, B> &a) {
	return out << "(" << a.x << ", " << a.y << ")";
}

template <class A> ostream& operator << (ostream& out, const vector<A> &v) {
	out << "[";
	forn(i, sz(v)) {
		if(i) out << ", ";
		out << v[i];
	}
	return out << "]";
}

mt19937 rnd(time(NULL));

const int INF = int(1e9);
const li INF64 = li(1e18);
const int MOD = int(1e9) + 7;
const ld EPS = 1e-9;
const ld PI = acos(-1.0);

const int N = 200 * 1000 + 13;
const int LOGN = 18;

int n, m, k;
pair<int, pt> e[N];
pt q[N];

bool read () {
	if (scanf("%d%d", &n, &m) != 2)
		return false;
	forn(i, m){
		scanf("%d%d%d", &e[i].y.x, &e[i].y.y, &e[i].x);
		--e[i].y.x, --e[i].y.y;
	}
	scanf("%d", &k);
	forn(i, k){
		scanf("%d%d", &q[i].x, &q[i].y);
		--q[i].x, --q[i].y;
	}
	return true;
}

int rk[N], p[N];

int getp(int a){
	return a == p[a] ? a : p[a] = getp(p[a]);
}

bool unite(int a, int b){
	a = getp(a), b = getp(b);
	if (a == b) return false;
	if (rk[a] < rk[b]) swap(a, b);
	rk[a] += rk[b];
	p[b] = a;
	return true;
}

int up[N][LOGN];
int mx[N][LOGN];
int d[N];

vector<pt> g[N];

void dfs(int v, int p = -1){
	for (auto it : g[v]){
		int u = it.x;
		int w = it.y;
		if (u != p){
			up[u][0] = v;
			mx[u][0] = w;
			d[u] = d[v] + 1;
			fore(i, 1, LOGN){
				up[u][i] = up[up[u][i - 1]][i - 1];
				mx[u][i] = max(mx[u][i - 1], mx[up[u][i - 1]][i - 1]);
			}
			dfs(u, v);
		}
	}
}

int calc(int v, int u){
	if (d[v] < d[u]) swap(v, u);
	int res = 0;
	for (int i = LOGN - 1; i >= 0; --i)
		if (d[up[v][i]] >= d[u]){
			res = max(res, mx[v][i]);
			v = up[v][i];
		}
	if (v == u) return res;
	for (int i = LOGN - 1; i >= 0; --i)
		if (up[v][i] != up[u][i]){
			res = max(res, mx[v][i]);
			res = max(res, mx[u][i]);
			v = up[v][i];
			u = up[u][i];
		}
	res = max(res, mx[v][0]);
	res = max(res, mx[u][0]);
	return res;
}

void solve() {
	sort(e, e + m);
	forn(i, n) p[i] = i, rk[i] = 1;
	li cost = 0;
	int cnt = n;
	forn(i, n) g[i].clear();
	forn(i, m){
		int v = e[i].y.x, u = e[i].y.y;
		int w = e[i].x;
		if (unite(v, u)){
			cost += e[i].x;
			g[v].pb(mp(u, w));
			g[u].pb(mp(v, w));
			--cnt;
		}
	}
	dfs(0);
	forn(i, k){
		int v = q[i].x, u = q[i].y;
		if (getp(v) != getp(u))
			printf("%lld\n", cnt == 2 ? cost : -1ll);
		else
			printf("%lld\n", cnt == 1 ? cost - calc(v, u) : -1ll);
	}
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	
	int tt = clock();
	
#endif
	
	cerr.precision(15);
	cout.precision(15);
	cerr << fixed;
	cout << fixed;

#ifdef MULTITEST
	int tc;
	scanf("%d", &tc);
	while(tc--){
		read();
#else
	while(read()) {	
#endif
		solve();
		
#ifdef _DEBUG
	cerr << "TIME = " << clock() - tt << endl;
	tt = clock();
#endif

	}
}