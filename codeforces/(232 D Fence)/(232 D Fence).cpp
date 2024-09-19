#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using pii = pair<int, int>;
using ppi = pair<pii, int>;

const int NN = 202020;

int a[NN];

const int _mx = 18;

ppi pos[NN];
int H[NN], Rank[NN], sa[NN];

void build_suf(int *s, int n) {
	int i, j = n, cnt, u;
	while(j--) Rank[j] = s[j]; pos[n] = {{-1, -1}, -1};
	Rank[n] = -1e9;
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
void Height(int *s, int n) {
	for(int i = 0, j, h = 0; i < n; i++) if(Rank[i] > 1) {
		h = max(0, h - 1), j = sa[Rank[i] - 1];
		while(i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
		H[Rank[i]] = h;
	}
}

int mn[NN][_mx];
void rmq(int n) {
	int i = 0, j = 0;
	while(i++ < n) mn[i][0] = H[i];
	while(++j < _mx) for(i = 0; i++ < n; ) {
		mn[i][j] = min(mn[i][j - 1], mn[min(n, i + (1 << j - 1))][j - 1]);
	}
}
int calc_min(int L, int R) {
	int k = 31 - __builtin_clz(R - L + 1);
	return min(mn[L][k], mn[R - (1 << k) + 1][k]);
}


int main() {
	
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", a + i);
	
	int nn = --n;
	for(int i = 0; i < nn; i++) a[i] -= a[i + 1];
	a[n++] = 1e9;
	for(int i = 0; i < nn; i++) a[n++] = -a[i];
	
	build_suf(a, n);
	Height(a, n);
	rmq(n);
	
	int q; scanf("%d", &q);
	while(q--) {
		int L, R; scanf("%d %d", &L, &R);
		
		int id = Rank[L + nn], len = R - L;
		if(len == 0) {printf("%d\n", nn); continue;}
		
		int st = 0, ed = id;
		while(ed - st > 1) {
			int md = st + ed >> 1;
			if(md == id || calc_min(md + 1, id) >= len) ed = md;
			else st = md;
		}
		l = ed;
		
		st = id, ed = n + 1;
		while(ed - st > 1) {
			int md = st + ed >> 1;
			if(id == md || calc_min(id + 1, md) >= len) st = md;
			else ed = md;
		}
		r = st + 1;
	}
	return 0;
}
