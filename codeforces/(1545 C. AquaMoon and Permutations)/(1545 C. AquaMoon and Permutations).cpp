#include <bits/stdc++.h>
using namespace std;

//#define ll long long

const int MOD = 998244353;
const int SIZE = 1005;

int n, ans;
vector<int> v;
int a[SIZE][SIZE], cnt[SIZE][SIZE];
bool vs[SIZE];

void solve() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        vs[i] = vs[i + n] = 0;
        for (int j = 1; j <= n; j++) cnt[i][j] = 0;
    }

    ans = 1;
    v.clear();

    for (int i = 1; i <= 2 * n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            cnt[a[i][j]][j]++;
        }
    }

    for (int i = 1; i <= n; i++) {
        int p = -1;

        for (int j = 1; j <= 2 * n; j++) {
            if (!vs[j]) {
                for (int k = 1; k <= n; k++) {
                    if (cnt[a[j][k]][k] == 1) {
                        p = j;
                        break;
                    }
                }
                if (p != -1) break;
            }
        }

        if (p == -1) {
            ans = (2 * ans) % MOD;
            for (int j = 1; j <= 2 * n; j++) {
                if (!vs[j]) {
                    p = j;
                    break;
                }
            }
        }

        vs[p] = true;

        for (int j = 1; j <= n; j++) cnt[a[p][j]][j]--;

        for (int j = 1; j <= 2 * n; j++) {
            if (!vs[j]) {
                for (int k = 1; k <= n; k++) {
                    if (a[j][k] == a[p][k]) {
                        vs[j] = true;
                        break;
                    }
                }
                if (vs[j]) {
                    for (int k = 1; k <= n; k++) cnt[a[j][k]][k]--;
                }
            }
        }

        v.push_back(p); 
    }

    cout << ans << '\n';
    for (int x : v) cout << x << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int tt;
    cin >> tt;
    while (tt--) solve();
}
