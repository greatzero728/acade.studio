#include <bits/stdc++.h>
using namespace std;

const int maxn = 200005;
const int mod = 1e9 + 7;
int n, m, ans, cur;
int l[maxn], r[maxn], ord[maxn], val[maxn];
bool in[maxn];

bool cmp(int x, int y) {
	return r[x] < r[y]; 
}

namespace Fenwick {
	int t[maxn * 2];
	void update(int v, int val) {
		for (; v <= 2 * n; v += (v & -v))
			t[v] = (t[v] + val) % mod;
	}
	int query(int v) {
		int res = 0;
		for (; v; v -= (v & -v))
			res = (res + t[v]) % mod;
		return res;
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &l[i], &r[i]);
		ord[i] = i;
	}
	sort(ord + 1, ord + 1 + n, cmp);
	scanf("%d", &m);
	while (m--) {
		int x;
		scanf("%d", &x);
		in[x] = true;
	}
	for (int i = 1; i <= n; i++) {
		int x = ord[i];
		val[x] = (Fenwick::query(r[x]) + mod - Fenwick::query(l[x]) + 1) % mod;
		Fenwick::update(l[x], val[x]); 
	}
	cur = 0;
	for (int i = n; i >= 1; i--) {
		int x = ord[i];
		Fenwick::update(l[x], mod - val[x]);
		if (in[x] && l[x] >= cur)
			ans = (1LL * ans + Fenwick::query(r[x]) + mod - Fenwick::query(cur) + 1) % mod, cur = l[x];
	}
	printf("%d\n", ans);
	return 0;
} 