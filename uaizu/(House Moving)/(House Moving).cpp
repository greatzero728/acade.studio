#include<bits/stdc++.h>

using namespace std;
using INT = long long;

const int NN = 101010;

int n;
INT B[NN];

INT calc(int u) {
    INT ans = 0;
    for(; u; u ^= u & -u) ans = max(ans, B[u]);
    return ans;
}

void update(int u, INT x) {
    for(; u <= n; u += u & -u) B[u] = max(B[u], x);
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        int x; scanf("%d", &x);
        INT mx = calc(x - 1);
        update(x, mx + x);
    }
    printf("%lld\n", (INT)n * (n + 1) / 2 - calc(n));
}