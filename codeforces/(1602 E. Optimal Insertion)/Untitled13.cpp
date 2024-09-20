#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long LL;
const int N = 1000005;

LL res;
int n, m;
int a[N], b[N], t[N];

int find(int x) {
	int l = 0, r = m, mid;
	while (l < r) {
		mid = l + r >> 1;
		if (b[mid] >= x) r = mid;
		else l = mid + 1;
	}
	return r;
}

priority_queue<int> q;
void change(int x) {
	if (q.empty() || x >= q.top()) {
		q.push(x);
	} else {
		res += q.top() - x, q.pop();
		q.push(x), q.push(x);
	}
}

LL calc(int l, int r) {
	if (r - l == 1) return 0ll;
	int mid = l + r >> 1, i = l, j = mid, k = 0;
	LL res = calc(l, j) + calc(j, r);
	while (i != mid && j != r) {
		if (a[j] < a[i]) res += mid - i, t[k++] = a[j++];
		else t[k++] = a[i++];
	}
	while (i != mid) t[k++] = a[i++];
	while (j != r) t[k++] = a[j++];
	for (i = l; i < r; ++i) a[i] = t[i - l];
	return res;
}

int main() {
	int task;
	for (scanf("%d", &task); task--; ) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++i) scanf("%d", a + i);
		for (int i = 0; i < m; ++i) scanf("%d", b + i);
		sort(b, b + m), res = 0;
		while (q.size()) q.pop();
		for (int i = 0; i < n; ++i) {
			int l = find(a[i]), r = find(a[i] + 1);
			change(r), change(l), res -= r - l;
		}
		printf("%lld\n", res / 2 + calc(0, n));
	}
	return 0;
}
