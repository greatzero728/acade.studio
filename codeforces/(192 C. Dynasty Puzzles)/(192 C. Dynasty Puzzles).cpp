#include <iostream>
#include <vector>
//#include <string>
//#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> names(n);
    for (int i = 0; i < n; i++) {
        cin >> names[i];
    }

    int dp[26][26];
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            dp[i][j] = 0;
        }
    }

    for (const string& name : names) {
        int len = name.size();
        char start = name[0];
        char end = name[len - 1];

        for (int j = 0; j < 26; j++) {
            if (dp[j][start - 'a'] > 0) {
                dp[j][end - 'a'] = max(dp[j][end - 'a'], dp[j][start - 'a'] + len);
            }
        }

        dp[start - 'a'][end - 'a'] = max(dp[start - 'a'][end - 'a'], len);
    }

    int max_len = 0;
    for (int i = 0; i < 26; i++) {
        max_len = max(max_len, dp[i][i]);
    }

    cout << max_len << endl;

    return 0;
}