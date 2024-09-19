#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    const int N = 1e3 + 1;
    const int M = 1e5 + 1;
    
    int a, b, m;
    cin >> a >> b >> m;
    
    vector<vector<int>> col(2 * N, vector<int>(N, 0));
    vector<int> u(M), v(M), in(2 * N, 0);
    int res = 0;
    
    for (int i = 1; i <= m; i++) {
        cin >> u[i] >> v[i];
        v[i] += a;
        ++in[u[i]], ++in[v[i]];
    }
    
    for (int i = 1; i <= a + b; i++) {
        res = max(res, in[i]);
    }

    for (int i = 1; i <= m; i++) {
        int x = 1, y = 1, temp, w;
        while (col[u[i]][x]) ++x;
        while (col[v[i]][y]) ++y;
        col[u[i]][x] = v[i];
        col[v[i]][y] = u[i];
        
        if (x != y) {
            temp = v[i], w = y;
            while (temp) {
                swap(col[temp][x], col[temp][y]);
                temp = col[temp][w];
                w ^= (x ^ y);
            }
        }
    }

    cout << res << "\n";

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= res; j++) {
            if (col[u[i]][j] == v[i]) {
                cout << j << " ";
                break;
            }
        }
    }
    cout << "\n";

    return 0;
}