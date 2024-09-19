#include<bits/stdc++.h>
using namespace std;

const int NN = 2020;

int a[NN], b[NN];

int main() {
    int n, k, p; scanf("%d %d %d", &n, &k, &p);
    for(int i = n; i--; ) scanf("%d", a + i);
    for(int i = k; i--; ) scanf("%d", b + i);
    sort(a, a + n);
    sort(b, b + k);
    int ans = INT_MAX;
    for(int i = 0; i + n <= k; i++) {
        int res = 0;
        for(int j = 0; j < n; j++) {
            res = max(res, abs(a[j] - b[i + j]) + abs(b[i + j] - p));
        }
        ans = min(ans, res);
    }
    printf("%d\n", ans);
}