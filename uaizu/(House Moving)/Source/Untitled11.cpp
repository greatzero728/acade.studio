#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, x;
ll b[100001];

ll find(int s) {
	ll res = 0;
	for (int i = s; i > 0; i = i & (i - 1))
		res = max(res, b[i]);
	return res;
}

void update(int s, ll val) {
	for (int i = s; i <= n; i += (i & -i))
		b[i] = max(b[i], val);
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		update(x, find(x - 1) + x);
	}
	printf("%lld\n", (ll)n * (n + 1) / 2 - find(n));
	return 0;
}
