#include <bits/stdc++.h>
using namespace std;

#define N	1000000

template<class T> struct compress {
	vector<T*> aa;

	void add(T &x) {
		aa.push_back(&x);
	}
	int go() {
		int cnt = 0;

		sort(begin(aa), end(aa), [&](T * a, T * b) {
			return *a < *b;
		});
		for (int i = 0; i + 1 < (int) aa.size(); i++)
			*aa[i] = *aa[i] == *aa[i + 1] ? cnt : cnt++;
		*aa.back() = cnt++;
		return cnt;
	}
};

template<class T> struct tree {
	int n; vector<T> ft;

	tree(int n_) {
		n = n_;
		ft.assign(n, 0);
	}
	void update(int i, const T &a) {
		while (i < n) {
			ft[i] += a;
			i |= i + 1;
		}
	}
	T query(int i) {
		T sum = 0;

		while (i >= 0) {
			sum += ft[i];
			i &= i + 1, --i;
		}
		return sum;
	}
	T query(int l, int r) {
		return query(r) - query(l - 1);
	}
};

int n, m, aa[N], bb[N], cc[N + 1];

void solve(int l0, int r0, int l1, int r1) {
	int m, p, pm, sm;
	static int kk[N + 1];

	if (l1 > r1)
		return;
	m = (l1 + r1) / 2, p = -1, pm = 0, sm = 0;

	kk[r0 + 1] = 0;
	for (int i = r0; i >= l0; i--)
		kk[i] = kk[i + 1] + (aa[i] < bb[m]);
	for (int i = l0; i <= r0 + 1; i++) {
		if (p == -1 || sm + kk[i] < pm)
			p = i, pm = sm + kk[i];
		sm += aa[i] > bb[m];
	}
	cc[p]++;
	solve(l0, min(n - 1, p + 1), l1, m - 1);
	solve(max(0, p), r0, m + 1, r1);
}

int main() {
	int t;

	scanf("%d", &t);
	while (t--) {
		int cnt; long long ans;
		vector<int> rr;
		compress<int> coords;

		scanf("%d%d", &n, &m);
		memset(cc, 0, (n + 1) * 4);
		for (int i = 0; i < n; i++)
			scanf("%d", &aa[i]), coords.add(aa[i]);
		for (int i = 0; i < m; i++)
			scanf("%d", &bb[i]), coords.add(bb[i]);
		cnt = coords.go();
		sort(bb, bb + m);
		solve(0, n - 1, 0, m - 1);
		for (int i = 0, j = 0; j < n; j++) {
			if (j == 0)
				while (cc[0]--)
					rr.push_back(bb[i++]);
			rr.push_back(aa[j]);
			while (cc[j + 1]--)
				rr.push_back(bb[i++]);
		}
		tree<int> ft(cnt);
		ans = 0;
		for (int x : rr) {
			ans += ft.query(x + 1, cnt - 1);
			ft.update(x, 1);
		}
		printf("%lld\n", ans);
	}
}