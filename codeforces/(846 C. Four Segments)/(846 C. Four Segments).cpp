#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<long long> p(n);
    p[0] = a[0];
    for (int i = 1; i < n; i++)
        p[i] = p[i - 1] + a[i];
    vector<long long> maxSuf(n + 1);
    vector<int> idx(n + 1);
    for (int i = n; i >= 0; i--) {
        maxSuf[i] = i ? p[i - 1] : 0;
        idx[i] = i;
        if (i + 1 <= n && maxSuf[i + 1] > maxSuf[i]) {
            maxSuf[i] = maxSuf[i + 1];
            idx[i] = idx[i + 1];
        }
    }

    long long ans = LLONG_MIN;
    int ansI, ansJ, ansK;
    for (int i = 0; i <= n; i++) {
        long long first = (i ? p[i - 1] : 0);
        for (int j = i; j <= n; j++) {
            long long second = (j ? p[j - 1] : 0) - (i ? p[i - 1] : 0);
            long long third = maxSuf[j] - (j ? p[j - 1] : 0);
            long long fourth = p[n - 1] - maxSuf[j];
            long long cur = first - second + third - fourth;
            if (cur > ans) {
                ans = cur;
                ansI = i, ansJ = j, ansK = idx[j];
            }
        }
    }
    cout << ansI << ' ' << ansJ << ' ' << ansK << endl;

    return 0;
}