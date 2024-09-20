#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int maxn = 35;
char s[maxn][maxn];
int v[maxn][maxn];
int x[maxn], y[maxn];
int c[maxn][maxn];
int p[maxn][maxn];
int xa[maxn], xb[maxn], ya[maxn], yb[maxn];
using pii = pair<int, int>;
vector<vector<pii> > w;
vector<pii> a;
void dfs(int u, int s)
{
    while (s >> u & 1) ++u;
    if (u == 14) return w.emplace_back(a), void();
    for (int i=u+1;i<14;++i)
        if (~s >> i & 1)
        {
            a.emplace_back(pii(u, i));
            dfs(u + 1, s | 1 << i);
            a.pop_back();
        }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i=0;i<n;++i) cin >> s[i];
    int k = 0;
    for (int i=0;i<n;++i)
        for (int j=0;j<=i;++j) p[i][j] = p[j][i] = k++;
    k = 0;
    memset(xa, -1, sizeof(xa));
    for (int i=0;i<n;++i)
        for (int j=0;j<m;++j)
            if (!v[i][j] && s[i][j] != '.')
            {
                v[i][j] = v[i + 1][j] = v[i][j + 1] = v[i + 1][j + 1] = 1;
                x[k] = i;
                y[k] = j;
                ++k;
            }
    for (int i=0;i<n;++i)
        for (int j=0;j<m;++j)
            if (s[i][j] != '.')
            {
                int p = s[i][j] >= 'A' && s[i][j] <= 'B' ? s[i][j] - 'A' + 26 : s[i][j] - 'a';
                if (xa[p] == -1) xa[p] = i, ya[p] = j;
                else xb[p] = i, yb[p] = j;
            }
    dfs(0, 0);
    int ans = 0;
    vector<pii> ok;
    auto col = [&](vector<pii>& p)
    {
        for (int i=0;i<7;++i)
        {
            int a = p[i].first, b = p[i].second;
            c[x[a]][y[a]] = c[x[a] + 1][y[a]] = c[x[a]][y[a] + 1] = c[x[a] + 1][y[a] + 1] = i;
            c[x[b]][y[b]] = c[x[b] + 1][y[b]] = c[x[b]][y[b] + 1] = c[x[b] + 1][y[b] + 1] = i;
        }
    };
    for (auto p : w)
    {
        col(p);
        int t = 0, o = 1;
        for (int i=0;i<28&&o;++i)
        {
            int k = ::p[c[xa[i]][ya[i]]][c[xb[i]][yb[i]]];
            if (t >> k & 1) o = 0;
            else t |= 1 << k;
        }
        ans += o;
        if (ans == 1 && o) ok = p;
    }
    cout << ans * 5040 << '\n';
    col(ok);
    for (int i=0;i<n;++i,cout<<'\n')
        for (int j=0;j<m;++j)
            if (s[i][j] == '.') cout << '.';
            else cout << c[i][j];
    return 0;
}