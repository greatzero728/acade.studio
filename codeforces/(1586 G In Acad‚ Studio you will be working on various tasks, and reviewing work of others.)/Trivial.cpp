#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using pii = pair<int, int>;
using ppi = pair<pii, bool>;

const int NN = 404040, mod = 1e9 + 7;

ppi p[NN];
int dp[NN], B[NN];

void update(int u, int x) {
    for(; u < NN; u += u & -u) B[u] = (B[u] + x) % mod;
}
int calc(int u) {
    int ans = 0;
    for(; u; u ^= u & -u) ans = (ans + B[u]) % mod;
    return ans;
}

int main() {
    int n; scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d %d", &p[i].x.x, &p[i].x.y);
        p[i].y = 0;
    }
    
    int m; scanf("%d", &m);
    while(m--) {
        int x; scanf("%d", &x);
        p[x].y = 1;
    }
    
    sort(p + 1, p + n + 1, [&](ppi a, ppi b) {
        return a.x.y < b.x.y;
    });
    
    for(int i = 1; i <= n; i++) {
        dp[i] = (calc(p[i].x.y) + mod - calc(p[i].x.x) + 1) % mod;
        update(p[i].x.x, dp[i]);
    }
    
    int t = 0, ans = 0;
    for(int i = n; i; i--) {
        update(p[i].x.x, mod - dp[i]);
        if(p[i].y && t <= p[i].x.x) {
            ans = (1LL * ans + calc(p[i].x.y) + mod - calc(t) + 1) % mod;
            t = p[i].x.x;
        }
    }
    printf("%d\n", ans);
}