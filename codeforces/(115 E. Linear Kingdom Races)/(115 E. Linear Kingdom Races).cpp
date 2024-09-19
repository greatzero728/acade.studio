#include <iostream>
#include <queue>
//#include <vector>
using namespace std;
const int N = 200010;

int n, m, a[N];
long long ans;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
vector<pair<int, int>> pos[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        pos[x].push_back({y, z});
        ans += z;
    }

    for (int i = 1; i <= n; i++) {
        while (!Q.empty() && Q.top().first < i) {
            Q.pop();
        }

        for (auto& v : pos[i]) {
            Q.push(v);
        }

        while (!Q.empty() && a[i]) {
            auto R = Q.top();
            Q.pop();

            int val = min(R.second, a[i]);
            a[i] -= val;
            R.second -= val;
            ans -= val;

            if (R.second) {
                Q.push(R);
            }
        }
    }

    cout << ans << endl;

    return 0;
}