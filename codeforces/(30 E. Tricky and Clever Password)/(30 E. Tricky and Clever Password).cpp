#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using pii = pair<int, int>;
using ppi = pair<pii, int>;

const int NN = 202020;

char s[NN];

int n;

//Only odd palindrome length is considered.
//z[i] means that the longest odd palindrome centered at i is [i - z[i] ... i + z[i]]
int z[NN];

void zpal(char *s, int n) {
	int i = 0, b = z[0] = 0;
	while(++i < n) {
		z[i] = b + z[b] < i ? 0 : min(z[b + b - i], b + z[b] - i);
		while(i + z[i] + 1 < n && i > z[i] && s[i + z[i] + 1] == s[i - z[i] - 1]) z[i]++;
		if(z[i] + i > z[b] + b) b = i;
	}
}

// 0-based
const int _mx = 18; // 1 << _mx > n

ppi pos[NN];
int H[NN], Rank[NN], sa[NN];

void build_suf(char *s, int n) {
	int i, j = n, cnt, u;
	while(j--) Rank[j] = s[j]; pos[n] = {{-1, -1}, -1};
	Rank[n] = 0;
	while(++j < _mx) {
		i = n, cnt = 0;
		while(i--) pos[i] = {{Rank[i], Rank[min(n, i + (1 << j))]}, i};
		sort(pos, pos + n);
		while(++i < n) {
			Rank[pos[i].y] = cnt + 1;
			if(pos[i].x != pos[i + 1].x) cnt++;
		}
		if(cnt == n) break;
	}
	while(i--) sa[Rank[i]] = i;
}
void Height(char *s, int n) {
	for(int i = 0, j, h = 0; i < n; i++) if(Rank[i] > 1) {
		h = max(0, h - 1), j = sa[Rank[i] - 1];
		while(i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
		H[Rank[i]] = h;
	}
}

struct RMQ {
	int mn[NN][_mx];
	void rmq_suf(int n) {
		int i = 0, j = 0;
		while(i++ < n) mn[i][0] = H[i];
		while(++j < _mx) for(i = 0; i++ < n; ) {
			mn[i][j] = min(mn[i][j - 1], mn[min(n, i + (1 << j - 1))][j - 1]);
		}
	}
	void rmq_min(int n) {
		int i = 0, j = 0;
		while(i++ < n) mn[i][0] = sa[i];
		while(++j < _mx) for(i = 0; i++ < n; ) {
			mn[i][j] = min(mn[i][j - 1], mn[min(n, i + (1 << j - 1))][j - 1]);
		}
	}
	int calc_min(int L, int R) {
		int k = 31 - __builtin_clz(R - L + 1);
		return min(mn[L][k], mn[R - (1 << k) + 1][k]);
	}
} rmq[2];

int prefix(int len) {
	int pos = n + 1;
	int k = Rank[pos];
	int st = 0, ed = k;
	while(ed - st > 1) {
		int md = st + ed >> 1;
		if(md == k || rmq[0].calc_min(md + 1, k) >= len) ed = md;
		else st = md;
	}
	int L = ed;
	
	st = k, ed = n + n + 2;
	while(ed - st > 1) {
		int md = st + ed >> 1;
		if(k == md || rmq[0].calc_min(k + 1, md) >= len) st = md;
		else ed = md;
	}
	int R = st;
	
	int left = rmq[1].calc_min(L, R);
	if(left < n) return left;
	return -1;
}

int main() {
    
	scanf("%s", s), n = strlen(s);
	
	zpal(s, n);
	
	int N = n;
	s[N++] = '$';
	
	for(int i = n, nn = n; i--; ) s[N++] = s[--nn];
	
	build_suf(s, N);
	Height(s, N);
	rmq[0].rmq_suf(N);
	rmq[1].rmq_min(N);
	
	int mx = 0;
	vector<pii> ans;
	for(int i = 0; i < n; i++) {
		int L = i - z[i], R = i + z[i];
		int st = 0, ed = n - R;
		while(ed - st > 1) {
			int md = st + ed >> 1;
			if(~prefix(md) && prefix(md) + md <= L) st = md;
			else ed = md;
		}
		if(!st) {
			if(mx < R - L + 1) {
				ans.clear();
				ans.push_back({L + 1, mx = R - L + 1});
			}
		}
		else if(~prefix(st) && prefix(st) + st <= L && mx < st + (R - L + 1) + st) {
			mx = st + (R - L + 1) + st;
			ans.clear();
			ans.push_back({prefix(st) + 1, st});
			ans.push_back({L + 1, R - L + 1});
			ans.push_back({n - st + 1, st});
		}
	}
	if(mx == n) {
		puts("1");
		printf("1 %d\n", n);
	}
	else {
		printf("%d\n", ans.size());
		for(pii p : ans) printf("%d %d\n", p.x, p.y);
	}
}