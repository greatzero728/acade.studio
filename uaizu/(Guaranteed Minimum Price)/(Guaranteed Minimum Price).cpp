#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<pair<int, int>> prices(N);
    for (int i = 0; i < N; ++i) {
        int a, t;
        cin >> a >> t;
        if (t == 0) {
            prices[i] = {a * 1.1, i};
        } else {
            prices[i] = {a, i};
        }
    }

    vector<int> lowerPrices;
    for (int i = 1; i < N; ++i) {
        if (prices[i].first < prices[0].first) {
            lowerPrices.push_back(i + 1);
        }
    }

    if (lowerPrices.empty()) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
        for (int i : lowerPrices) {
            cout << i << "\n";
        }
    }

    return 0;
}