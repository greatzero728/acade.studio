#include<bits/stdc++.h>



using namespace std;



typedef long long INT;

typedef pair<int, int> pii;



#define NN 510

#define MM 610000

#define x first

#define y second



bitset<NN> dp[NN][NN][2];

pii L[MM], R[MM];

int ans[MM];

char s[NN][NN];

int n, m, Q;



inline int solve(int st, int ed, vector<int> res) {

	if(st > ed) return 0;

	int md = (st + ed) / 2;

	

	vector<int> vec[2];

	

	for(int i=n; i; i--) {

		dp[i][md][0].reset();

		if(s[i][md] == '#') continue;

		dp[i][md][0].set(i);

		if(i != n) dp[i][md][0] |= dp[i+1][md][0];

	}

	for(int i=1; i<=n; i++) {

		dp[i][md][1].reset();

		if(s[i][md] == '#') continue;

		dp[i][md][1].set(i);

		if(i != 1) dp[i][md][1] |= dp[i-1][md][1];

	}

	for(int j=md-1; j>=st; j--) {

		for(int i=n; i; i--) {

			dp[i][j][0].reset();

			if(s[i][j] == '#') continue;

			dp[i][j][0] |= dp[i][j+1][0];

			if(i != n) dp[i][j][0] |= dp[i+1][j][0];

		}

	}

	for(int j=md+1; j<=ed; j++) {

		for(int i=1; i<=n; i++) {

			dp[i][j][1].reset();

			if(s[i][j] == '#') continue;

			dp[i][j][1] |= dp[i][j-1][1];

			if(i != 1) dp[i][j][1] |= dp[i-1][j][1];

		}

	}

	

	vec[0].clear(), vec[1].clear();

	for(auto id : res) {

		if(L[id].y <= md and R[id].y >= md) {

			if((dp[L[id].x][L[id].y][0] & dp[R[id].x][R[id].y][1]).count()) ans[id] = 1;

			else ans[id] = 0;

		} else if(R[id].y < md) vec[0].push_back(id);

		else vec[1].push_back(id);

	}

	

	solve(st, md-1, vec[0]);

	solve(md+1, ed, vec[1]);

}



vector<int> res;



int main(){

#ifndef ONLINE_JUDGE

	freopen("in.in","r",stdin);

	freopen("out.out","w",stdout);

#endif

	cin >> n >> m;

	for(int i=1; i<=n; i++) scanf("%s", s[i] + 1);

	cin >> Q;

	for(int i=1; i<=Q; i++) {

		scanf("%d %d %d %d", &L[i].x, &L[i].y, &R[i].x, &R[i].y);

		res.push_back(i);

	}

	

	solve(1, m, res);

	for(int i=1; i<=Q; i++) {

		if(ans[i]) puts("Yes");

		else puts("No");

	}

}


               