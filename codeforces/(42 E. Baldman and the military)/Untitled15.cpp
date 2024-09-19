#include <bits/stdc++.h>

#define itn int
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

struct Dsu {
	int n;
	vector<int> p, rk;
	
	Dsu(int _n): n(_n), p(_n), rk(_n) {
		iota(all(p), 0);
	}
	
	int get(int v) {
		return v == p[v] ? v : p[v] = get(p[v]);
	}
	
	bool merge(int u, int v) {
		u = get(u), v = get(v);
		if (u == v) {
			return false;
		}
		if (rk[u] < rk[v]) {
			swap(u, v);
		}
		p[v] = u;
		if (rk[u] == rk[v]) {
			++rk[u];
		}
		return true;
	}
};

struct Edge {
	int u, v;
	int w;
	
	bool operator <(const Edge& ot) const {
		return w < ot.w;
	}
};

void solve() {
	int n = nxt();
	int m = nxt();
	vector<Edge> eds(m);
	for (auto& [u, v, w] : eds) {
		u = nxt() - 1, v = nxt() - 1;
		w = nxt();
	}
	sort(all(eds));
	Dsu dsu(n);
	vector<Edge> real_edges;
	long long total = 0;
	for (auto e : eds) {
		if (dsu.merge(e.u, e.v)) {
			real_edges.push_back(e);
			total += e.w;
		}
	}
	if ((int)real_edges.size() < n - 2) {
		int q = nxt();
		while (q--) {
			nxt();
			nxt();
			cout << "-1\n";
		}
		return;
	}
	if ((int)real_edges.size() == n - 2) {
		int q = nxt();
		while (q--) {
			int u = nxt() - 1;
			int v = nxt() - 1;
			cout << (dsu.get(u) == dsu.get(v) ? -1 : total) << "\n";
		}
		return;
	}
	
	vector<vector<pair<int, int>>> a(n);
	for (auto [u, v, w] : real_edges) {
		a[u].push_back({v, w});
		a[v].push_back({u, w});
	}
	
	vector<pair<int, int>> par(n, {-1, 0}), jump(n, {0, 0});
	vector<int> tin(n), tout(n);
	int timer = 0;
	vector<int> h(n);
	auto dfs = [&](auto self, int v, int p) -> void {
		tin[v] = timer++;
		if (p > -1) {
			if (h[p] - 2 * h[jump[p].first] + h[jump[jump[p].first].first] == 0) {
				jump[v] = {jump[jump[p].first].first, max({par[v].second, jump[p].second, jump[jump[p].first].second})};
			} else {
				jump[v] = par[v];
			}
		}
		for (auto [x, w] : a[v]) {
			if (x != p) {
				par[x] = {v, w};
				h[x] = h[v] + 1;
				self(self, x, v);
			}
		}
		tout[v] = timer;
	};
	dfs(dfs, 0, -1);
	auto is_par = [&](int u, int v) {
		return tin[u] <= tin[v] && tout[u] >= tout[v];
	};
	auto lca = [&](int u, int v) {
		while (!is_par(u, v)) {
			if (is_par(jump[u].first, v)) {
				u = par[u].first;
			} else {
				u = jump[u].first;
			}
		}
		return u;
	};
	auto f = [&](int u, int l) {
		int ans = 0;
		while (u != l) {
			if (is_par(jump[u].first, l)) {
				ans = max(ans, par[u].second);
				u = par[u].first;
			} else {
				ans = max(ans, jump[u].second);
				u = jump[u].first;
			}
		}
		return ans;
	};
	
	int q = nxt();
	while (q--) {
		int u = nxt() - 1, v = nxt() - 1;
		int l = lca(u, v);
		cout << total - max(f(u, l), f(v, l)) << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int t = 1; // nxt();
	while (t--) {
		solve();
	}

	return 0;
}