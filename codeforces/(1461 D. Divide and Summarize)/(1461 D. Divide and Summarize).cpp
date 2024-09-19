#include<bits/stdc++.h>

using namespace std;
using INT = long long;

map<INT, bool>mp;

int a[101010], b[101010];

void solve(int L, int R) {
	int mn = *min_element(a + L, a + R + 1);
	int mx = *max_element(a + L, a + R + 1);
	int md = mn + mx >> 1;
	for(int i = L, nn = L; i <= R; i++) if(a[i] <= md) b[nn++] = a[i];
	for(int i = R, nn = R; i >= L; i--) if(a[i] > md) b[nn--] = a[i];
	
	INT sum = 0;
	for(int i = L; i <= R; i++) sum += a[i] = b[i];
	mp[sum] = 1;
	
	if(L < R) {
		for(int i = L; i <= R; i++) if(a[i] > md) {
			if(L < i) solve(L, i - 1);
			solve(i, R);
			return;
		}
	}
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n, q; scanf("%d %d", &n, &q);
		for(int i = 1; i <= n; i++) scanf("%d", a + i);
		
		mp.clear(), solve(1, n);
		while(q--) {
			INT s; scanf("%lld", &s);
			if(mp.find(s) == mp.end()) puts("No");
			else puts("Yes");
		}
	}
	return 0;
}
