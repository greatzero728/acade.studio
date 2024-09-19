#include <bits/stdc++.h>

using namespace std;

const int NN = 505050;

int a[NN], cnt[NN], cur_cnt[NN];

int main() {
    int m, k, n, s; scanf("%d %d %d %d", &m, &k, &n, &s);
    for(int i = 1; i <= m; i++) scanf("%d", a + i);
    
    int num = 0;
    while(s--) {
        int b; scanf("%d", &b);
        if(!cnt[b]++) num++;
    }
    for(int L = 1, R = 1, cur_num = 0; L <= m; L++) {
        for(; R <= m && (cur_num < num || R - L < k); R++) {
            if(++cur_cnt[a[R]] == cnt[a[R]]) cur_num++;
        }
        if(cur_num == num && R - L >= k) {
            int del_left = max((L - 1) / k - (n - 1), 0) * k + (L - 1) % k;
            int del_inrange = R - L - k;
            int total = del_left + del_inrange;
            if(total <= m - n * k && (L - 1) / k + 1 + (m - R + 1) / k >= n) {
                printf("%d\n", total);
                for(int i = 1; i <= del_left; i++) printf("%d ", i);
                for(int i = L; i < R && del_inrange > 0; i++) {
                    if(cur_cnt[a[i]]-- > cnt[a[i]]) printf("%d ", i), del_inrange--;
                }
                return 0;
            }
        }
        if(cur_cnt[a[L]]-- == cnt[a[L]]) cur_num--;
    }
    puts("-1");
}