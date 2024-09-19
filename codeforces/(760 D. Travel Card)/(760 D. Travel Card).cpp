#include <bits/stdc++.h>

using namespace std;

const int NN = 101010;

int times[NN], cost[NN];

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> times[i];
    }

    for (int i = 1; i <= n; i++) {
        int pos_2 = upper_bound(times + 1, times + i + 1, times[i] - 90) - times - 1;
        
        int pos_3 = upper_bound(times + 1, times + i + 1, times[i] - 1440) - times - 1;

        cost[i] = min(cost[i - 1] + 20, min(cost[pos_2] + 50, cost[pos_3] + 120));

        cout << cost[i] - cost[i - 1] << endl;
    }

    return 0;
}
