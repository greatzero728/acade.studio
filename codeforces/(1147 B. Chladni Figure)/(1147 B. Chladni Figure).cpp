#include <bits/stdc++.h>

using namespace std;

int n, m;

bool check(int k, const set<pair<int, int>>& g) {
    for (auto i : g) {
        int a = (i.first + k) % n;
        int b = (i.second + k) % n;
        if (g.find(make_pair(min(a, b), max(a, b))) == g.end()) {
            return false;
        }
    }
    return true;
}

int main() {
    cin >> n >> m;
    set<pair<int, int>> g;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a -= 1;
        b -= 1;
        g.insert(make_pair(min(a, b), max(a, b)));
    }

    for (int i = 1; i < n; ++i) {
        if (n % i == 0) {
            if (!check(i, g)) {
                continue;
            }
            cout << "Yes" << endl;
            return 0;
        }
    }

    cout << "No" << endl;
    return 0;
}
