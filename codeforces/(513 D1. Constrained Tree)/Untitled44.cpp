#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef double ld;
const int maxN = (int)1e5 + 10;
vector < int > le[maxN], ri[maxN];
int n;
void imp() {
    cout << "IMPOSSIBLE";
    exit(0);
}
int t[maxN][2];
int mx[maxN];
int val[maxN], val_left[maxN];
void solve(int v, int lim) {
    if (v == lim) {
        if ((!le[v].empty()) || (!ri[v].empty())) {
            imp();
        }
        return ;
    }
    int lim2 = val_left[v];
    if (le[v].empty()) {
        t[v][1] = v + 1;
        solve(v + 1, lim);
        return ;
    }
    if (ri[v].empty()) {
        t[v][0] = v + 1;
        solve(v + 1, lim);
        return ;
    }
    for (int k = v + 1; k <= lim2; k++) {
        if (mx[k] > lim2) imp();
    }
    if (ri[v][0] <= lim2) imp();
    t[v][0] = v + 1;
    t[v][1] = lim2 + 1;
    solve(v + 1, lim2);
    solve(lim2 + 1, lim);
}
void dfs(int v) {
    if (t[v][0] != 0) {
        dfs(t[v][0]);
    }
    cout << v << " ";
    if (t[v][1] != 0) {
        dfs(t[v][1]);
    }
}
int main() {
    //freopen("input.txt", "r", stdin);
    srand(239);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    int q;
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int a, b;
        string s;
        cin >> a >> b >> s;
        if (a >= b) imp();
        if (s == "LEFT") {
            le[a].push_back(b);
        }
        else {
            ri[a].push_back(b);
        }
    }
    for (int i = 1; i <= n; i++) {
        sort(le[i].begin(), le[i].end());
        sort(ri[i].begin(), ri[i].end());
        if (!le[i].empty()) mx[i] = max(mx[i], le[i].back());
        if (!ri[i].empty()) mx[i] = max(mx[i], ri[i].back());
    }
    for (int i = n; i >= 1; i--) {
        val[i] = i;
        if (mx[i] != 0) {
            for (int j = i + 1; j <= mx[i]; j++) val[i] = max(val[i], val[j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!le[i].empty()) {
            val_left[i] = i + 1;
            for (int j = i + 1; j <= le[i].back(); j++) {
                val_left[i] = max(val_left[i], val[j]);
            }
        }
    }
    solve(1, n);
    dfs(1);
    return 0;
}

