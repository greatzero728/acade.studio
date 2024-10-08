#include <bits/stdc++.h>

using i64 = long long;

int timeToInt(std::string s) {
    int hh = std::stoi(s.substr(0, 2));
    int mm = std::stoi(s.substr(3));
    return hh * 60 + mm;
}

std::string intToTime(int x) {
    int hh = x / 60;
    int mm = x % 60;
    std::string s;
    s += '0' + hh / 10;
    s += '0' + hh % 10;
    s += ':';
    s += '0' + mm / 10;
    s += '0' + mm % 10;
    return s;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int m, n, k;
    std::cin >> m >> n >> k;
    
    std::vector<std::string> name(m);
    std::map<std::string, int> id;
    for (int i = 0; i < m; i++) {
        std::cin >> name[i];
        id[name[i]] = i;
    }
    std::vector<int> cost(m);
    for (int i = 0; i < m; i++) {
        std::cin >> cost[i];
    }
    
    std::array<bool, 1440> free;
    free.fill(true);
    for (int i = 0; i < 4; i++) {
        std::string s;
        std::cin >> s;
        
        int S = timeToInt(s.substr(0, 5));
        int T = timeToInt(s.substr(6));
        
        for (int i = S; i <= T; i++) {
            free[i] = false;
        }
    }
    
    std::array<int, 1441> pre{};
    for (int i = 0; i < 1440; i++) {
        pre[i + 1] = pre[i] + free[i];
    }
    
    int freePerDay = pre[1440];
    int totalFree = freePerDay * k;
    
    std::vector<std::array<int, 4>> people;
    
    for (int i = 0; i < n; i++) {
        std::string name;
        int day;
        std::string time;
        int money;
        std::cin >> name >> day >> time >> money;
        
        if (!id.count(name)) {
            continue;
        }
        
        int t = timeToInt(time);
        t = (day - 1) * freePerDay + pre[t];
        
        people.push_back({t, cost[id[name]], money, i});
    }
    
    std::sort(people.begin(), people.end());
    
    n = people.size();
    
    std::vector<int> point;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < 1440; j++) {
            if (free[j]) {
                point.push_back(i * 1440 + j);
            }
        }
    }
    
    std::vector dp(n + 1, std::vector<int>(totalFree + 1));
    for (int i = 0; i < n; i++) {
        auto [t, cost, money, j] = people[i];
        dp[i + 1] = dp[i];
        for (int j = t - cost; j >= 0; j--) {
            dp[i + 1][j + cost] = std::max(dp[i + 1][j + cost], dp[i][j] + money);
        }
        for (int j = 1; j <= totalFree; j++) {
            dp[i + 1][j] = std::max(dp[i + 1][j], dp[i + 1][j - 1]);
        }
    }
    
    std::cout << dp[n][totalFree] << "\n";
    
    std::vector<std::tuple<int, int, std::string, int, std::string>> ans;
    int t = totalFree;
    for (int i = n - 1; i >= 0; i--) {
        auto [lim, cost, money, j] = people[i];
        while (t && dp[i + 1][t - 1] == dp[i + 1][t]) {
            t--;
        }
        if (t <= lim && t >= cost && dp[i + 1][t] == dp[i][t - cost] + money) {
            int end = point[t - 1];
            t -= cost;
            int start = point[t];
            ans.emplace_back(j + 1, start / 1440 + 1, intToTime(start % 1440)
                , end / 1440 + 1, intToTime(end % 1440));
        } else {
            assert(dp[i + 1][t] == dp[i][t]);
        }
    }
    std::reverse(ans.begin(), ans.end());
    
    std::cout << ans.size() << "\n";
    for (auto [a, b, c, d, e] : ans) {
        std::cout << a << " " << b << " " << c << " " << d << " " << e << "\n";
    }
    
    return 0;
}