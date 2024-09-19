#include <bits/stdc++.h>
using namespace std;
#define N 100010
#define prob pair <double, double> 

int n, q;
double p[N];
prob a[N * 4];

prob push_up(prob p1, prob p2) {
	prob rt;
	rt.first = p1.first * p2.first / (1 - p1.second * (1 - p2.first));
	rt.second = p1.second * p2.first * (1 - p2.second) / (1 - p1.second * (1 - p2.first)) + p2.second;
	return rt;
}

void build (int v, int l, int r) {
	if (l == r) {
		a[v] = {p[l], p[r]};
		return;
	}
	int m = (l + r) / 2;
	build (v * 2, l, m);
	build (v * 2 + 1, m + 1, r);
	a[v] = push_up(a[v * 2], a[v * 2 + 1]);
}

void update(int v, int l, int r, int i, double x) {
	if (l == r) {
		a[v] = {x, x};
		return;
	}
	int m = (l + r) / 2;
	if (i <= m) update(v * 2, l, m, i, x);
	else update(v * 2 + 1, m + 1, r, i, x);
	a[v] = push_up(a[v * 2], a[v * 2 + 1]);
}

prob query(int v, int l, int r, int L, int R) {
	if (L <= l && r <= R) {
		return a[v];
	}
	int m = (l + r) / 2;
	if (m >= L) {
		prob p1 = query(v * 2, l, m, L, R);
		if (m + 1 <= R) {
			prob p2 = query(v * 2 + 1, m + 1, r, L, R);
			return push_up(p1, p2);
		}
		else return p1;
	}
	else return query(v * 2 + 1, m + 1, r, L, R);
}

int main(){
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		int u, v;
		cin >> u >> v;
		p[i] = 1.0 * u / v;
	}
	build(1, 1, n);
	while (q--) {
		int t;
		cin >> t;
		if (t == 1){
			int i, u, v;
			cin >> i >> u >> v;
			update(1, 1, n, i, 1.0 * u / v);
		}
		else {
			int l, r;
			cin >> l >> r;
			printf("%.10f\n", query(1, 1, n, l, r).first);
		}
	}
}