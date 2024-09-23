#include <bits/stdc++.h>
using namespace std;

signed main() {
    int n;
    cin >> n;
    int a[n];
    for(auto &x : a) {
        cin >> x;
    }
    string s;
    cin >> s;
    sort(a, a+n, greater<>());
    int cnt = 0;
    for(int i = 1; i < n; i++) {
        if(s[i] != s[i-1]) {
            cnt++;
        }
    }
    int right = cnt, left = cnt-1;
    vector<int> ans = {(s[0] == 'R'? -1 : 1)*a[right++]};
    bool prev = s[0] == 'R';
    int sum = ans.back();
    for(int i = 1; i < n; i++) {
        if(s[i] == s[i-1]) {
            prev ^= 1;
            ans.push_back((prev? -1 : 1)*a[right++]);
        } else {
            ans.push_back((s[i] == 'R'? -1 : 1)*a[left--]);
        }
        sum += ans.back();
        if(s[i] == 'L' && sum <= 0 || s[i] == 'R' && sum >= 0) {
            cout << -1;
            return 0;
        } 
    }
    for(int i = 0; i < n; i++) {
        cout << abs(ans[i]) << " " << (ans[i] < 0? "R" : "L") << endl;
    }
}   