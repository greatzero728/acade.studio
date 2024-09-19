#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
        }
        for (int col = (m % 3 == 0) ? 1 : 0; col < m; col += 3) {
            for (int row = 0; row < n; ++row) {
                grid[row][col] = 'X';
            }
            if (col >= m - 3) {
                break;
            }
            int con = (n == 1 || (grid[1][col + 1] != 'X' && grid[1][col + 2] != 'X')) ? 0 : 1;
            grid[con][col + 1] = 'X';
            grid[con][col + 2] = 'X';
        }
        for (auto &row: grid) {
            cout << row << "\n";
        }
    }
    return 0;
}