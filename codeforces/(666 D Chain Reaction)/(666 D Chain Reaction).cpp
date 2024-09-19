#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using pii = pair<int, int>;

vector<pii> p(4), ans(4);

const int inf = 1e9;

int solve() {
    int best_ans = inf;
    
    return best_ans;
}

void swap_xy() {
    for(int i = 0; i < 4; i++) {
        swap(p[i].x, p[i].y);
        swap(ans[i].x, ans[i].y);
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        for(int i = 0; i < 4; i++) {
            scanf("%d %d", &p[i].x, &p[i].y);
        }
        
        int ans_y = solve();
        swap_xy();
        int ans_x = solve();
        swap_xy();

        if(ans_y > ans_x) ans_y = ans_x;
        else solve();

        if(ans_y == inf) puts("-1");
        else {
            printf("%d\n", ans_y);
            for(int i = 0; i < 4; i++) {
                printf("%d %d\n", ans[i].x, ans[i].y);
            }
        }
    }
    return 0;
}
