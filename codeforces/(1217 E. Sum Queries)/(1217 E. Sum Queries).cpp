#include<bits/stdc++.h>

using namespace std;
using INT = long long;

const int NN = 202020, MM = NN << 1, inf = 2e9;

int a[NN], l, r;
int f[9] = {1};

#define mid (L + R >> 1)

int ls[MM], rs[MM], nn;
INT mn[MM][9], ans[MM];

void push_up(int u) {
	ans[u] = min(ans[ls[u]], ans[rs[u]]);
	for(int i = 9; i--; ) {
		ans[u] = min(ans[u], mn[ls[u]][i] + mn[rs[u]][i]);
		mn[u][i] = min(mn[ls[u]][i], mn[rs[u]][i]);
	}
}

void update(int u, int L) {
	ans[u] = inf;
	for(int i = 9; i--; ) {
		if(a[L] / f[i] % 10) mn[u][i] = a[L];
		else mn[u][i] = inf;
	}
}

int build(int L, int R) {
	int u = nn++;
	if(R - L == 1) update(u, L);
	else {
		ls[u] = build(L, mid);
		rs[u] = build(mid, R);
		push_up(u);
	}
	return u;
}

void update(int u, int L, int R) {
	if(l <= L && R <= r) update(u, L);
	else {
		if(l < mid) update(ls[u], L, mid);
		if(mid < r) update(rs[u], mid, R);
		push_up(u);
	}
}

INT Mn[9], Ans;

void calc(int u, int L, int R) {
	if(l <= L && R <= r) {
		Ans = min(Ans, ans[u]);
		for(int i = 9; i--; ) {
			Ans = min(Ans, Mn[i] + mn[u][i]);
			Mn[i] = min(Mn[i], mn[u][i]);
		}
	}
	else {
		if(l < mid) calc(ls[u], L, mid);
		if(mid < r) calc(rs[u], mid, R);
	}
}

int main() {
	for(int i = 1; i < 9; i++) f[i] = 10 * f[i - 1];
	
    int n, m; scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", a + i);
    
    build(1, n + 1);
    
    while(m--) {
        int t; scanf("%d %d", &t, &l);
        if(t == 1) {
        	scanf("%d", a + l);
            r = l + 1, update(0, 1, n + 1);
        }
        else {
            scanf("%d", &r), r++;
            for(int i = 9; i--; ) Mn[i] = inf;
            Ans = inf;
            calc(0, 1, n + 1);
        }
    }
}