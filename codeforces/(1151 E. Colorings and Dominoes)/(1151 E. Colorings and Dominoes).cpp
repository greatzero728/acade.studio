#include <bits/stdc++.h>

using namespace std;
using INT = long long;

const int NN = 303030, mod = 998244353;

char s[NN];
int f[NN] = {1}, dp[NN];

int main() {

	int n, m; scanf("%d %d", &n, &m);
	bool a[n + 1][m + 1];
	
	int sum = 0;
	for(int i = 0; i < n; i++) {
		scanf("%s", s);
		for(int j = m; j--; ) sum += a[i][j] = s[j] == 'o';
	}
	
	for(int i = 1; i < NN; i++) f[i] = (f[i - 1] << 1) % mod;
	for(int i = 1; i < NN; i++) {
		dp[i] += dp[i - 1]; //?0
		dp[i] += dp[i - 2]; //01
		dp[i] += dp[i - 2]; //11 (left)
		dp[i] += f[i - 2]; //11 (right)
	}
	
	int ans = 0;
	for(int I = n; I--; ) {
		for(int i = 0, j = 0; i < m; i = j) {
			for(; j < m && a[I][i] == a[I][j]; j++);
			if(a[I][i]) ans = (ans + (INT)dp[j - i] * f[sum - (j - i)]) % mod;
		}
	}
	for(int J = m; J--; ) {
		for(int i = 0, j = 0; i < n; i = j) {
			for(; j < n && a[i][J] == a[j][J]; j++);
			if(a[i][J]) ans = (ans + (INT)dp[j - i] * f[sum - (j - i)]) % mod;
		}
	}
	printf("%d\n", ans);
	return 0;
}