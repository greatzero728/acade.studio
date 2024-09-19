#include<bits/stdc++.h>

using namespace std;

vector<pair<int, int>> gr2;

int f(int cu, int mn, int mx, vector<pair<pair<int, int>, pair<int, int>>> &gr){
	if(gr[cu].first.first <= cu || gr[cu].first.second >= gr[cu].second.first || gr[cu].second.second > mx){
		cout << "IMPOSSIBLE\n";
		exit(0);
	}
	int nxt = cu + 1;
	if(~gr[cu].first.second){
		gr2[cu].first = nxt;
		nxt = f(nxt, gr[cu].first.second, min(mx, gr[cu].second.first - 1), gr);
		if(nxt > gr[cu].second.first){
			cout << "IMPOSSIBLE\n";
			exit(0);
		}
	}
	int nmn = max(mn, gr[cu].second.second);
	if(nmn < nxt)return nxt;
	gr2[cu].second = nxt;
	return f(nxt, nmn, mx, gr);
}

void pf(int x){
	if(!~x)return;
	pf(gr2[x].first);
	cout << x + 1 << ' ';
	pf(gr2[x].second);
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m; cin >> n >> m;
	vector<pair<pair<int, int>, pair<int, int>>> gr(n, {{n, -1}, {n, -1}});
	gr2.resize(n, {-1, -1});
	vector<int> P(n, -1);
	for(int i = 0; i < m; ++i){
		int a, b;
		string s; cin >> a >> b >> s;
		a--, b--;
		if(b <= a){
			cout << "IMPOSSIBLE\n";
			return 0;
		}
		if(s == "LEFT"){
			gr[a].first.first = min(gr[a].first.first, b);
			gr[a].first.second = max(gr[a].first.second, b);
		}
		else {
			gr[a].second.first = min(gr[a].second.first, b);
			gr[a].second.second = max(gr[a].second.second, b);
		}
	}
	f(0, n - 1, n - 1, gr);
	pf(0);
	cout << '\n';
}
