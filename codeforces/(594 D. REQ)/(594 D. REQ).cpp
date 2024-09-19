#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int N = 2e5 + 2;
const int MAX = 1e6 + 2;
int mul(int x,int y) {
    return (long long) x * y % mod;
}

int pw(int x,int y) {
    int ret = 1;
    while (y) {
        if (y & 1) ret = mul(ret, x);
        x = mul(x, x);
        y >>= 1;
    }
    return ret;
}
struct query {
    int l, r, id;
    bool operator < (const query &q) {
        return r < q.r;
    }
};

int n, q; 
int a[N], f[N], last[MAX];
vector<int> pr[MAX];
int fw[N], ans[N];
vector<query> Q;
void sieve() {
	for (int i = 2; i < MAX; ++i) if (pr[i].empty()) {
		for (int j = i; j < MAX; j += i) pr[j].push_back(i);
	}
}
int main() {
    ios_base::sync_with_stdio(false);
    sieve();
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    cin >> q;
    for (int i = 1; i <= q; ++i) {
        int l, r; cin >> l >> r;
        Q.push_back({l, r, i});
    }

}