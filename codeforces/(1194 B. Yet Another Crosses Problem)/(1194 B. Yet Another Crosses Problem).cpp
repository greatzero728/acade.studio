#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int q;
    cin >> q;
    while (q--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> grid(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                char c;
                cin >> c;
                grid[i][j] = (c == '*');
            }
        }

        vector<int> rowCounts(n, 0);
        vector<int> colCounts(m, 0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!grid[i][j]) {
                    rowCounts[i]++;
                    colCounts[j]++;
                }
            }
        }

        int ans = n * m;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int curr = rowCounts[i] + colCounts[j] - (1 - grid[i][j]);
                ans = min(ans, curr);
            }
        }

        cout << ans << "\n";
    }
}