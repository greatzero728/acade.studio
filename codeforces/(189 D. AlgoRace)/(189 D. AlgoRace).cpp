#include<bits/stdc++.h>

using namespace std;

const int NN = 66, inf = 1e9;

int d[NN][NN][NN], dp[NN][NN][NN];

int main() {
	
	int n, m, r; scanf("%d %d %d", &n, &m, &r);
	
	for(int i = 0; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			for(int k = 1; k <= n; k++) dp[i][j][k] = inf;
		}
	}
	for(int k = 1; k <= m; k++) {
		for(int u = 1; u <= n; u++) {
			for(int v = 1; v <= n; v++) scanf("%d", d[k][u] + v);
		}
		for(int w = 1; w <= n; w++) {
			for(int u = 1; u <= n; u++) {
				for(int v = 1; v <= n; v++) d[k][u][v] = min(d[k][u][v], d[k][u][w] + d[k][w][v]);
			}
		}
		for(int u = 1; u <= n; u++) {
			for(int v = 1; v <= n; v++) dp[0][u][v] = min(dp[0][u][v], d[k][u][v]);
		}
	}
	
	for(int k = 1; k <= n; k++) {
		for(int u = 1; u <= n; u++) {
			for(int v = 1; v <= n; v++) {
				for(int w = 1; w <= n; w++) dp[k][u][v] = min(dp[k][u][v], dp[k - 1][u][w] + dp[0][w][v]);
			}
		}
	}
	
	while(r--) {
		int u, v, k; scanf("%d %d %d", &u, &v, &k);
		printf("%d\n", dp[min(k, n)][u][v]);
	}
}