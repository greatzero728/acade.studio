#include<bits/stdc++.h>

using namespace std;
using INT = long long;

const int NN = 101010;

int horizon[NN][5], vertical[NN][5], n, m;
INT dp[NN][32];

int main() {
	cin>>n>>m;
	for(int i = 1; i < m; i++) {
		for(int j = 0; j < n; j++) cin>>horizon[i][j];
	}
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) cin>>vertical[i][j];
	}
	
	memset(dp, 0x3f, sizeof dp);
	dp[1][0] = 0;
	for(int i = 1; i < m; i++) {
		for(int j = 0; j < 1 << n; j++) {
			for(int k = 0; k < n; k++) if(!((j >> k) & 1)) {
				dp[i][j ^ (1 << k)] = min(dp[i][j ^ (1 << k)], dp[i][j] + horizon[i][k]);
			}
			for(int k = 0; k < n; k++) {
				if(((j >> k) & 1) ^ ((j >> (k + 1) % n) & 1)) dp[i][j] += vertical[i][k];
				dp[i + 1][j] = dp[i][j];
			}
		}
	}
	
	printf("%lld\n", dp[m][(1 << n) - 1]);
}
