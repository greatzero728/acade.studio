#include <bits/stdc++.h>

#ifdef LOCAL
	#define debug(x) cerr << (#x) << ": " << x << endl
#else
	#define debug(x) ;
#endif

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define rep1(i, n) for (int i = 1; i < (n); ++i)
#define rep1n(i, n) for (int i = 1; i <= (n); ++i)
#define repr(i, n) for (int i = (n) - 1; i >= 0; --i)
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define sz(a) (int)(a.size())
#define each(x, a) for (auto &x : a)

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using str = string;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pair<int, int>>;
using vvi = vector<vi>;

mt19937 rnd(0);

const int BIG = 1e9, LG = 30, maxN = 1e5, maxM = 2e5, K = 17;
const ll INF = 1e18;

struct Edge {
	int u, v, w;
	Edge(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w) {}
	bool operator<(const Edge& other) const {
		return w < other.w;
	}
} e[maxM];

struct Item {
	int p, cnt;
	Item(int p = 0, int cnt = 1) : p(p), cnt(cnt) {}
} DSU[maxN];

int test = 1, n, m, a, b, c, q, comp, tin[maxN], tout[maxN], it;
pi up[maxN][K];
ll ans;
vpi gr[maxN];

int get(int u) {
	return u == DSU[u].p ? u : DSU[u].p = get(DSU[u].p);
}

void unite(int u, int v) {
	u = get(u);
	v = get(v);
	if (u == v)
		return;
	if (DSU[u].cnt < DSU[v].cnt)
		swap(u, v);
	DSU[v].p = u;
	DSU[u].cnt += DSU[v].cnt;
}

void dfs(int u, int p, int pw) {
	tin[u] = it++;
	up[u][0] = mp(p, pw);
	for (auto &[v, w] : gr[u]) {
		if (v == p)
			continue;
		dfs(v, u, w);
	}
	tout[u] = it;
}

bool is_ancestor(int u, int v) {
	return tin[u] <= tin[v] && tin[v] < tout[u];
}

int get(int u, int v) {
	int ans = 0;
	repr(i, K) {
		if (!is_ancestor(up[u][i].first, v)) {
			ans = max(ans, up[u][i].second);
			u = up[u][i].first;
		}
		if (!is_ancestor(up[v][i].first, u)) {
			ans = max(ans, up[v][i].second);
			v = up[v][i].first;
		}
	}
	if (!is_ancestor(u, v))
		ans = max(ans, up[u][0].second);
	if (!is_ancestor(v, u))
		ans = max(ans, up[v][0].second);
	return ans;
}

void solve() {
	cin >> n >> m;
	rep(i, m) {
		cin >> a >> b >> c;
		a--, b--;
		e[i] = Edge(a, b, c);
	}
	sort(e, e + m);
	rep(i, n) {
		DSU[i] = Item(i);
		gr[i].clear();
	}
	comp = n;
	ans = 0;
	rep(i, m) {
		if (get(e[i].u) != get(e[i].v)) {
			gr[e[i].u].eb(e[i].v, e[i].w);
			gr[e[i].v].eb(e[i].u, e[i].w);
			ans += e[i].w;
			unite(e[i].u, e[i].v);
			comp--;
		}
	}
	cin >> q;
	if (comp == 1) {
		dfs(0, 0, 0);
		rep1(i, K) {
			rep(j, n) {
				up[j][i] = mp(up[up[j][i - 1].first][i - 1].first, max(up[j][i - 1].second, up[up[j][i - 1].first][i - 1].second));
			}
		}
	}
	while (q--) {
		cin >> a >> b;
		a--, b--;
		if (comp > 2)
			cout << "-1\n";
		else if (comp == 2) {
			if (get(a) == get(b))
				cout << "-1\n";
			else
				cout << ans << "\n";
		}
		else
			cout << ans - get(a, b) << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
		cin >> test;
	#endif
	while (test--)
		solve();
	return 0;
}