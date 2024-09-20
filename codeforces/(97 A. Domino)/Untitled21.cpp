#include<iostream>
#include<cstring>
#include<vector>
#include<cassert>
using namespace std;
using LL = long long;

int main(){

#ifdef LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    vector<pair<int, int> > pos1[28];
    for(int i = 0; i < n; i++){
        cin >> g[i];
        for(int j = 0; j < m; j++){
            if (g[i][j] == '.') continue;
            int id = -1;
            if (islower(g[i][j])) id = g[i][j] - 'a';
            else id = 26 + g[i][j] - 'A';
            pos1[id].push_back({i, j});
        }
    }
    vector<pair<int, int> > pos2[14];

    vector<vector<bool> > v(n, vector<bool>(m));
    
    for(int i = 0, k = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if (v[i][j] || g[i][j] == '.') continue;
            for(int a = 0; a < 2; a++){
                for(int b = 0; b < 2; b++){
                    v[i + a][j + b] = true;
                    pos2[k].push_back({i + a, j + b});
                }
            }
            k++;
        }
    }

    int cnt = 0;

    vector<vector<int> > a(n, vector<int>(m));

    vector<vector<int> > ans;

    auto dfs = [&](auto &&dfs, int u, int state) -> void {
        if (u == 7){
            bool ok = true;
            vector<vector<bool> > mark(7, vector<bool>(7));
            for(int i = 0; i < 28; i++){
                int x = a[pos1[i][0].first][pos1[i][0].second];
                int y = a[pos1[i][1].first][pos1[i][1].second];
                if (x > y) swap(x, y);
                if (mark[x][y]){
                    ok = false;
                    break;
                }
                mark[x][y] = true;
            }
            if (ok){
                ans = a;
                cnt += 1;
            }
            return;
        }

        int t = 0;
        while(state >> t & 1) t++;

        for(auto [x, y] : pos2[t]){
            a[x][y] = u;
        }

        for(int j = t + 1; j < 14; j++){
            if (state >> j & 1) continue;
            for(auto [x, y] : pos2[j]){
                a[x][y] = u;
            }
            dfs(dfs, u + 1, state | (1 << t) | (1 << j));
        }
    };

    dfs(dfs, 0, 0);
    cout << 1LL * cnt * 5040 << '\n';
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if (g[i][j] == '.') cout << '.';
            else cout << ans[i][j];
        }
        cout << '\n';
    }

}