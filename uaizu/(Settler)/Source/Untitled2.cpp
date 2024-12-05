#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<functional>
#include<iomanip>
#include<queue>
#include<ciso646>
#include<utility>
#include<set>
#include<map>
#include<stack>
using namespace std;
typedef long long ll;
const ll mod = 1000000007;
const ll INF = mod * mod;
typedef pair<int, int> P;
typedef pair<ll, ll> LP;
typedef vector<int> vec;
typedef long double ld;
#define rep(i,n) for(int i=0;i<n;i++)
#define per(i,n) for(int i=n-1;i>=0;i--)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define Rep(i,sta,n) for(int i=sta;i<n;i++)
#define stop char nyaa;cin>>nyaa;

struct edge {
	int to, cap, rev;
};

vector<edge> G[100000];
bool used[100000];
int banned[100000];
void add_edge(int from, int to) {
	G[from].push_back({ to, 1, (int)G[to].size() });
	G[to].push_back({ from, 0, (int)G[from].size() - 1 });
}

int l, r;
int dfs(int v, int t, int f) {
	if (v == t)return f;
	used[v] = true;
	for (int i = 0; i < (int)G[v].size(); ++i) {
		edge& e = G[v][i];
		if (!used[e.to] && !banned[e.to] &&e.cap > 0) {
			int d = dfs(e.to, t, min(f, e.cap));
			if (d > 0) {
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}
int max_flow(int s, int t) {
	int flow = 0;
	for (;;) {
		memset(used, 0, sizeof(used));
		int f = dfs(s, t, mod);
		if (f == 0)return flow;
		flow += f;
	}
}
bool isodd[6000];
int flow;
int rest;
void del(int x){
    if(banned[x])return;
    banned[x]=true;
    --rest;
    int nxt = -1;
    if(isodd[x]){
        for(auto& e : G[x]){
            if(e.to == r && e.cap == 0){
                --flow;
                e.cap = 1;
                G[e.to][e.rev].cap = 0;
            }
            else if(e.to != r &&e.cap == 1){
                e.cap = 0;
                G[e.to][e.rev].cap = 1;
                nxt = e.to;
            }
        }
        if(nxt!=-1){
            for(auto& e : G[nxt]){
                if(e.to == l && e.cap == 1){
                    e.cap = 0;
                    G[e.to][e.rev].cap = 1;
                }
            }
        }
    }
    else {
        for(auto& e : G[x]){
            if(e.to == l && e.cap == 1){
                --flow;
                e.cap = 0;
                G[e.to][e.rev].cap = 1;
            }
            else if(e.to != l &&e.cap == 0){
                e.cap = 1;
                G[e.to][e.rev].cap = 0;
                nxt = e.to;
            }
        }
        if(nxt!=-1){
            for(auto& e : G[nxt]){
                if(e.to == r && e.cap == 0){
                    e.cap = 1;
                    G[e.to][e.rev].cap = 0;
                }
            }
        }
    }
}

void add(int x){
    banned[x]=false;
    rest++;
}

void solve() {
	int n, k;
	cin >> n >> k;
	int x[6666], y[6666];
	rep(i, n) {
		cin >> x[i] >> y[i];
    }
	vector<int> odd, even;
	rep(i, n) {
		if (x[i] % 2 ==1 && y[i] % 2 == 0) {
			even.push_back(i);
		}
		else if (x[i] % 2 == 0 && y[i] % 2 == 0) {
			even.push_back(i);
		}
		else odd.push_back(i);
	}
	l = n, r = n + 1;
	rep(i, even.size()) {
		add_edge(l, even[i]);
	}
	rep(j, odd.size()) {
		add_edge(odd[j], r);
		isodd[odd[j]] = true;
	}
	rep(i, even.size()) {
		rep(j, odd.size()) {
			ll dx = x[even[i]] - x[odd[j]];
			ll dy = y[even[i]] - y[odd[j]];
			ll dif = dx * dx + dy * dy;
			if (dif < 4) {
				add_edge(even[i], odd[j]);
			}
		}
	}
	rest = n;
	flow = max_flow(l, r);
	if (n - flow < k) {
		cout << -1 << endl; return;
	}
	vector<int> ans;
    int cur = 0;
    int use = 0;
    while(cur<n){
        if(banned[cur]){
            ++cur;
            continue;
        }
        ++use;
        del(cur);
        vector<int> dels;
        for(auto &e : G[cur]){
            if(e.to!=l&&e.to!=r&&!banned[e.to]){
                dels.push_back(e.to);
                del(e.to);
            }
        }
        flow += max_flow(l, r);
        if(rest-flow+use>=k){
            ans.push_back(cur);
        }
        else {
            --use;
            for(auto e : dels)add(e);
            flow += max_flow(l,r);
        }
        ++cur;
    }
	rep(i,k) {
		cout << ans[i]+1 << endl;
	}
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	solve();
		return 0;
}
