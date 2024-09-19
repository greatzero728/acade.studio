#include <bits/stdc++.h>
using namespace std;

const int maxn = 1510;
int n, q, tim, f[maxn], c[maxn][maxn], vis[maxn * maxn];
vector<pair<int, int>> S[maxn][maxn];

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &c[i][j]);
        }
    }
    for (int i = n; i; i--) {
        for (int j = n; j; j--) {
            vector<pair<int, int>> V = {{0, c[i][j]}};
            for (auto p : S[i][j + 1]) V.push_back(p);
            for (auto p : S[i + 1][j]) V.push_back(p);
            for (auto p : S[i + 1][j + 1]) V.push_back(p);
            stable_sort(V.begin(), V.end()), tim++;
            for (auto p : V) if (vis[p.second] ^ tim) {
                vis[p.second] = tim;
                S[i][j].emplace_back(p.first + 1, p.second);
                if (S[i][j].size() > q) break;
            }
            int t = S[i][j].size() > q ? S[i][j][q].first : INT_MAX;
            f[1]++, f[min({n - i + 2, n - j + 2, t})]--;
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("%d\n", f[i] += f[i - 1]);
    }
    return 0;
}