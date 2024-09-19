#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<vector<char>> ans(n, vector<char>(n, '='));
    for (int i = 0; i < n; i++) {
        ans[i][i] = 'X';
    }
    vector<int> type2;
    for (int i = 0; i < n; i++) {
        if (s[i] == '2') {
            type2.push_back(i);
        }
    }
    if (type2.size() == 1 || type2.size() == 2) {
        cout << "NO\n";
        return;
    }
    for (int i = 0; i < type2.size(); i++) {
        int j = (i + 1) % type2.size();
        ans[type2[i]][type2[j]] = '+';
        ans[type2[j]][type2[i]] = '-';
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << ans[i][j];
        }
        cout << "\n";
    }
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}