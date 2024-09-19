#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    vector<int> t(n + 1);
    vector<int> sumA(n + 1);
    vector<int> sumT(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }

    for (int i = 1; i <= n; i++) {
        sumA[i] = sumA[i - 1] + a[i];
        sumT[i] = sumT[i - 1] + a[i] * t[i];
    }

    int maxSum = 0;
    for (int i = 1; i <= n - k + 1; i++) {
        int currentSum = sumT[n] - sumT[i + k - 1] + sumA[i + k - 1] - (sumA[i - 1] - sumT[i - 1]);
        maxSum = max(maxSum, currentSum);
    }

    cout << maxSum << endl;
}