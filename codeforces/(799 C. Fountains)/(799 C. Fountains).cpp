#include <bits/stdc++.h>
#define y second
#define x first

using namespace std;
using pii = pair<int, int>;
using ppc = pair<pii, char>;

const int NN = 101010, inf = 1e9;

int b[NN], p[NN], Mx, N;
int n, c, d;

ppc fountain[NN];

// 1)
int solve_1() {
    int max_beauty_in_coin = -inf;
    int max_beauty_in_diamond = -inf;
    for(int i = 0; i < n; i++) {
        int beauty = fountain[i].x.x;
        int cost = fountain[i].x.y;
        char type = fountain[i].y;
        if(type == 'C') {
            if(cost <= c) max_beauty_in_coin = max(max_beauty_in_coin, beauty);
        }
        else {
            if(cost <= d) max_beauty_in_diamond = max(max_beauty_in_diamond, beauty);
        }
    }
    return max(0, max_beauty_in_coin + max_beauty_in_diamond);
}

int B[NN];

int calc_max_beauty(int u) {
    int ans = -inf;
    for(; u; u ^= u & -u) ans = max(ans, B[u]);
    return ans;
}
void maximize_beauty(int u, int beauty) {
    for(; u < NN; u += u & -u) B[u] = max(B[u], beauty);
}

int solve_sub_problem() {
    int ans = 0;
    for(int i = 0; i < NN; i++) B[i] = -inf;
    for(int i = 0; i < N; i++) {
        if(Mx - p[i] > 0) ans = max(ans, calc_max_beauty(Mx - p[i]) + b[i]);
        maximize_beauty(p[i], b[i]);
    }
    return ans;
}

// 2)
int solve_2() {
    int ans = 0;
    
    // 2-1)
    N = 0, Mx = c;
    for(int i = 0; i < n; i++) {
        int beauty = fountain[i].x.x;
        int cost = fountain[i].x.y;
        char type = fountain[i].y;
        if(type == 'C') b[N] = beauty, p[N] = cost, N++;
    }
    ans = max(ans, solve_sub_problem());
    
    // 2-2)
    N = 0, Mx = d;
    for(int i = 0; i < n; i++) {
        int beauty = fountain[i].x.x;
        int cost = fountain[i].x.y;
        char type = fountain[i].y;
        if(type == 'D') b[N] = beauty, p[N] = cost, N++;
    }
    ans = max(ans, solve_sub_problem());
    return ans;
}

int main() {
    scanf("%d %d %d", &n, &c, &d);
    for(int i = 0; i < n; i++) {
        scanf("%d %d %c", &fountain[i].x.x, &fountain[i].x.y, &fountain[i].y);
    }
    printf("%d\n", max(solve_1(), solve_2()));
}