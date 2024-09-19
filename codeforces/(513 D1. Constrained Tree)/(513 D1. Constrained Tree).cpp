#include<bits/stdc++.h>

using namespace std;
const int NN = 121;

void end() {puts("IMPOSSIBLE"), exit(0);}

vector<int> son[NN][2], ans;
int rt;

void dfs(int mn, int mx) {
    rt = mn;
    
    int lmn = NN, lmx = 0;
    for(int v : son[mn][0]) lmn = min(lmn, v), lmx = max(lmx, v);
    int lst = mn + 1, led = lmx;
    if(lst <= lmx) dfs(lst, lmx);
    
    ans.push_back(mn);
    
    int rmn = NN, rmx = 0;
    for(int v : son[mn][1]) rmn = min(rmn, v), rmx = max(rmx, v);
    int rst = rt + 1, red = max(mx, rmx);
    if(rmn < NN || rst <= red) {
        if(rmn <= rt) end();
        dfs(rst, red);
    }
}

int main() {
    int n, c; scanf("%d %d", &n, &c);
    while(c--) {
        int a, b; string c;
        cin>>a>>b>>c;
        if(b <= a) end();
        son[a][c[0] == 'R'].push_back(b);
    }
    dfs(1, n);
    for(int x : ans) printf("%d ", x);
    return 0;
}