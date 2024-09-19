#include <bits/stdc++.h>
using namespace std;

int getGrundy(long long size) {
    if (size < 4) return 0;
    if (size < 16) return 1;
    if (size < 82) return 2;
    if (size < 6724) return 0;
    if (size < 50626) return 3;
    return (size < 50626LL * 50626LL) ? 1 : 2;
}

string findWinner(int g) {
    return g ? "Furlo" : "Rublo";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<long long> a(n);
    for (auto &x : a) {
        cin >> x;
    }

    int g = 0;
    for (const auto &x : a) {
        g ^= getGrundy(x);
    }

    cout << findWinner(g) << '\n';

    return 0;
}