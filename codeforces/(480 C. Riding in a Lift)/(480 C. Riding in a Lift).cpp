#include<bits/stdc++.h>

using namespace std;

const int NN = 5050, mod = 1e9 + 7;

int dp[NN][NN];

void add(int i, int st, int ed, int add) {
	if(st > ed) return;
	dp[i][st] = (dp[i][st] + add) % mod;
	dp[i][ed + 1] = (dp[i][ed + 1] + mod - add) % mod;
}

int main() {
	int n, a, b, k; scanf("%d %d %d %d", &n, &a, &b, &k);
	dp[0][a] = 1;
	for(int i = 0; i < k; i++) {
		for(int j = 1; j <= n; j++) {
			int d = abs(j - b);
			if(j < b) {
				add(i + 1, j + 1, b - 1, dp[i][j]);
				add(i + 1, max(j - d + 1, 1), j - 1, dp[i][j]);
			}
			else if(j > b) {
				add(i + 1, b + 1, j - 1, dp[i][j]);
				add(i + 1, j + 1, min(j + d - 1, n), dp[i][j]);
			}
		}
		for(int j = 1; j <= n; j++) dp[i + 1][j] = (dp[i + 1][j] + dp[i + 1][j - 1]) % mod;
	}
	
	int ans = 0;
	for(int i = 1; i <= n; i++) if(i ^ b) ans = (ans + dp[k][i]) % mod;
	printf("%d\n", ans);
	return 0;
}