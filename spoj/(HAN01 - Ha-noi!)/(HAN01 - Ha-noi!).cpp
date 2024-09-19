#include<bits/stdc++.h>

using namespace std;
using INT = long long;

const int NN = 77;

INT f[NN] = {0, 1};
vector<int> ans[4];

void move(int n, int st, int ed, INT k) {
    int id = 6 - st - ed;
    if(k <= f[n - 1]) {
        ans[st].push_back(n);
        move(n - 1, st, id, k);
    }
    else {
        k -= f[n - 1];
        
        ans[ed].push_back(n);
        if(k == 1) {
            for(int i = n - 1; i >= 1; i--) {
                ans[id].push_back(i);
            }
            return;
        }
        k--;
        move(n - 1, id, ed, k);
    }
}

int main() {
    for(int i = 2; i <= NN; i++) {
        f[i] = f[i - 1] * 2 + 1;
    }
    
    int t; scanf("%d", &t);
    while(t--) {
        for(int i = 1; i <= 3; i++) ans[i].clear();
        int n; INT k; scanf("%d %lld", &n, &k);
        move(n, 1, 2, k);
        for(int i = 1; i <= 3; i++) {
            printf("%d: ", i);
            for(int j = 0; j < ans[i].size(); j++) {
                if(j) printf("|");
                printf("%d", ans[i][j]);
            }
            puts("");
        }
    }
}