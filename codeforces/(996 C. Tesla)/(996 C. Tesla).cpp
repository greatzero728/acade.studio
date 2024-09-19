#include<bits/stdc++.h>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<vector<int>> grid(4, vector<int>(n));
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < n; ++j)
            cin >> grid[i][j];

    int cars = k;
    vector<vector<int>> ans;

    for (int i = 0; i < n; ++i) {
        if (grid[0][i]) cars++;
        if (grid[3][i]) cars++;
    }

    while (cars) {
        for (int i = 0; i < n; ++i) {
            if (grid[0][i] == grid[1][i] && grid[0][i]) {
                ans.push_back({grid[1][i], 1, i + 1});
                grid[1][i] = 0;
                cars--;
            }
            if (grid[2][i] == grid[3][i] && grid[2][i]) {
                ans.push_back({grid[2][i], 4, i + 1});
                grid[2][i] = 0;
                cars--;
            }
        }

        vector<int> temp = grid[1];
        vector<int> temp2 = grid[2];

        if (find(temp.begin(), temp.end(), 0) == temp.end() && 
            find(temp2.begin(), temp2.end(), 0) == temp2.end()) {
            break;
        } else if (accumulate(temp.begin(), temp.end(), 0) + 
                   accumulate(temp2.begin(), temp2.end(), 0) == 0 || !cars) {
            cars = 0;
            break;
        }

        for (int i = 1; i < n; ++i) {
            if (temp[i - 1] && !grid[1][i]) {
                grid[1][i] = temp[i - 1];
                grid[1][i - 1] = 0;
                ans.push_back({temp[i - 1], 2, i + 1});
            }
        }

        for (int i = n - 2; i >= 0; --i) {
            if (temp2[i + 1] && !grid[2][i]) {
                ans.push_back({temp2[i + 1], 3, i + 1});
                grid[2][i] = temp2[i + 1];
                grid[2][i + 1] = 0;
            }
        }

        if (temp2[0] && !grid[1][0]) {
            ans.push_back({temp2[0], 2, 1});
            grid[1][0] = temp2[0];
            grid[2][0] = 0;
        }

        if (temp[n - 1] && !grid[2][n - 1]) {
            ans.push_back({temp[n - 1], 3, n});
            grid[2][n - 1] = temp[n - 1];
            grid[1][n - 1] = 0;
        }
    }

    if (cars || ans.size() > 20000) {
        cout << -1 << endl;
    } else {
        cout << ans.size() << endl;
        for (auto &a : ans) {
            cout << a[0] << " " << a[1] << " " << a[2] << endl;
        }
    }

    return 0;
}
