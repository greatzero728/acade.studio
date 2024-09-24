#include <bits/stdc++.h>

using namespace std;

int main() {
    int A, B, C, N;
    scanf("%d %d %d %d", &A, &B, &C, &N);
    set<tuple<int, int, int>> s;
    while(N--) {
        int x, y, z; scanf("%d %d %d", &x, &y, &z);
        s.insert(make_tuple(x, y, z));
    }
    long long surfaceArea = 2LL * A * B + 2LL * B * C + 2LL * C * A;
    for (auto [x, y, z] : s) {
        if (x > 0 && s.count(make_tuple(x - 1, y, z)) == 0) surfaceArea++;
        if (x < A - 1 && s.count(make_tuple(x + 1, y, z)) == 0) surfaceArea++;
        if (y > 0 && s.count(make_tuple(x, y - 1, z)) == 0) surfaceArea++;
        if (y < B - 1 && s.count(make_tuple(x, y + 1, z)) == 0) surfaceArea++;
        if (z > 0 && s.count(make_tuple(x, y, z - 1)) == 0) surfaceArea++;
        if (z < C - 1 && s.count(make_tuple(x, y, z + 1)) == 0) surfaceArea++;
    }
    for (auto [x, y, z] : s) {
        if (x == 0) surfaceArea--;
        if (x == A - 1) surfaceArea--;
        if (y == 0) surfaceArea--;
        if (y == B - 1) surfaceArea--;
        if (z == 0) surfaceArea--;
        if (z == C - 1) surfaceArea--;
    }
    printf("%lld\n", surfaceArea);
}