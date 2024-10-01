#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> idx2;
        for (int i = 0; i < n; i++) {
            if (s[i] == '2') idx2.push_back(i);
        }
        if (idx2.size() == 1 || idx2.size() == 2) {
            cout << "NO" << endl;
            continue;
        }
        cout << "YES" << endl;
        vector<vector<char>> mat(n, vector<char>(n, '='));
        for (int i = 0; i < n; i++) mat[i][i] = 'X';
        for (int i = 0; i < idx2.size(); i++) {
            int j = (i + 1) % idx2.size();
            mat[idx2[i]][idx2[j]] = '+';
            mat[idx2[j]][idx2[i]] = '-';
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << mat[i][j];
            }
            cout << endl;
        }
    }
    return 0;
}