#include<bits/stdc++.h>

using namespace std;

const int NN = 101010;

int a[NN];

int main() {
	
	int n; scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	
	for(int i = 2; i < n; i++) if(a[i - 1] > (a[i] ^ a[i + 1])) {
		puts("1"), exit(0);
	}
	
	int ans = n;
	for(int ia = 1; ia <= n; ia++) {
		int left = 0;
		for(int ib = ia; ib <= n; ib++) {
			left ^= a[ib];
			for(int ic = ib + 1; ic <= n; ic++) {
				int right = 0;
				for(int id = ic; id <= n; id++) {
					right ^= a[id];
					if(left > right) ans = min(ans, ib - ia + id - ic);
				}
			}
		}
	}
	if(ans == n) ans = -1;
	printf("%d\n", ans);
	return 0;
}
