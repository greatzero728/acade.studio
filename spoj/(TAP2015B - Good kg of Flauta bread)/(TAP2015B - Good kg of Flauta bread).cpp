#include <bits/stdc++.h>

using namespace std;
using INT = long long;

int L, K;
bool can_split(INT mn) {
    int ans = 0;
    INT current_sum = 0;
    for (int i = 1; i <= L; i++) {
        current_sum += 2 * i - 1;
        if (current_sum >= mn) {
            ans++;
            current_sum = 0;
        }
    }
    return ans >= K;
}

int main() {
    while (~scanf("%d %d", &L, &K)) {
        INT total_sum = 1LL * L * L;
        INT st = 1, ed = total_sum + 1;

        while(ed - st > 1) {
            INT md = (st + ed) / 2;
            if(can_split(md)) st = md;
            else ed = md;
        }
        printf("%lld\n", st);
    }
}
