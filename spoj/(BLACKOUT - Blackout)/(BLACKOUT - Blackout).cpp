#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define ll long long

vector<pair<int, ll>> values;

const int N = 1e3+5;

int dp[N][N];

int f(int ind, int k){
	if(ind == 0) return 0;
	if(dp[ind][k] != -1) return dp[ind][k];
	dp[ind][k] = f(ind-1, k);
	if(k>=values[ind-1].se) dp[ind][k] = max(dp[ind][k], f(ind-1, k-values[ind-1].se) + values[ind-1].fi);
	return dp[ind][k];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	memset(dp, -1, sizeof(dp));

	int n, m, q, k;
	cin >> n >> m >> q >> k;

	vector<vector<int>> grid(n, vector<int>(m));

	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
			cin >> grid[i][j];
		}
	}

	vector<vector<ll>> grid_sum(n+1, vector<ll>(m+1, 0));

	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m; ++j){
			grid_sum[i][j] = grid[i-1][j-1] + grid_sum[i-1][j] + grid_sum[i][j-1] - grid_sum[i-1][j-1];
		}
	}

	for(int i=0; i<q; ++i){
		int i1, j1, i2, j2;
		cin >> i1 >> j1 >> i2 >> j2;
		int area = (i2-i1+1) * (j2-j1+1);
		ll sum = grid_sum[i2][j2] - grid_sum[i2][j1-1] - grid_sum[i1-1][j2] + grid_sum[i1-1][j1-1];
		values.pb({area, sum});
	}

	cout << f(q, k);

	return 0;	
}