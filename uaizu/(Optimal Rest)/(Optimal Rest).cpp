#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using namespace std::chrono;
using psi = pair<string, int>;

const int NN = 101010, MM = 32 * NN;

char s[NN];

int dp[MM];

int main() {
#ifndef ONLINE_JUDGE
    auto start_time = steady_clock::now();
#endif

    int t; scanf("%d", &t);
    vector<psi> vec;
    for(int i = 1; i <= 64; i *= 2) {
        string s = "R" + to_string(i);
        int val = 64 / i, x = val;
        for(int j = 0; x; j++) {
            vec.push_back({s, val});
            s += '.';
            x /= 2, val += x;
        }
    }
    
    for(int i = 1; i < MM; i++) {
#ifndef ONLINE_JUDGE
        auto current_time = steady_clock::now();
        auto elapsed_time = duration_cast<milliseconds>(current_time - start_time).count();
        if (elapsed_time >= 1000) break;
#endif
        dp[i] = 1e9;
        for(psi p: vec) if(i >= p.y) {
            dp[i] = min(dp[i], dp[i - p.y] + (int)p.x.size());
        }
    }
    
    while(t--) {
        scanf("%s", s);
        int all = 0, val = 0;
        for(int i = 0, x = 0; s[i]; i++) {
            if(s[i] == 'R') all += val, x = 0;
            else if(isdigit(s[i])) {
                x = 10 * x + s[i] - '0';
                if(!isdigit(s[i + 1])) x = 64 / x, val = x;
            }
            else x /= 2, val += x;
        }
        all += val;
        
        string ans;
        while(all) {
            psi mn = {"R", all};
            for(psi p: vec) if(all >= p.y && dp[all - p.y] + p.x.size() == dp[all]) {
                if(p.x + "R" < mn.x + "R") mn = p;
            }
            ans += mn.x;
            all -= mn.y;
        }
        printf("%s\n", ans.c_str());
    }
}