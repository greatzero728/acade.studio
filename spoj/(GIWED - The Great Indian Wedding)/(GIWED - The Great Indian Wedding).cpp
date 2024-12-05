#include<bits/stdc++.h>

using namespace std;

const int NN = 121;

int X1[NN], X2[NN], xrr[NN], nx;
int Y1[NN], Y2[NN], yrr[NN], ny;
bool vst[NN][NN];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
vector<int> area;

bool out(int x, int y) {
    return x < 0 || y < 0 || x >= nx || y >= ny;
}

int s;

void dfs(int x, int y) {
    vst[x][y] = 1, s += (xrr[x + 1] - xrr[x]) * (yrr[y + 1] - yrr[y]);
    for(int k = 4; k--; ) {
        int X = x + dx[k], Y = y + dy[k];
        if(!out(X, Y) && !vst[X][Y]) {
            vst[X][Y] = 1, dfs(X, Y);
        }
    }
}

void solve() {
    int M, N, K, L; scanf("%d %d %d %d", &M, &N, &K, &L);
    
    nx = 0, xrr[nx++] = 0;
    ny = 0, yrr[ny++] = 0;
    for(int i = 1; i <= K; i++) {
        scanf("%d %d %d %d", X1 + i, Y1 + i, X2 + i, Y2 + i);
        xrr[nx++] = X1[i];
        if(X2[i] < M) xrr[nx++] = X2[i];
        yrr[ny++] = Y1[i];
        if(Y2[i] < N) yrr[ny++] = Y2[i];
    }
    sort(xrr, xrr + nx), nx = unique(xrr, xrr + nx) - xrr, xrr[nx] = M;
    sort(yrr, yrr + ny), ny = unique(yrr, yrr + ny) - yrr, yrr[ny] = N;
    
    for(int i = 0; i < nx; i++) {
        for(int j = 0; j < ny; j++) vst[i][j] = 0;
    }
    for(int k = 1; k <= K; k++) {
        X1[k] = lower_bound(xrr, xrr + nx, X1[k]) - xrr;
        X2[k] = lower_bound(xrr, xrr + nx, X2[k]) - xrr;
        Y1[k] = lower_bound(yrr, yrr + ny, Y1[k]) - yrr;
        Y2[k] = lower_bound(yrr, yrr + ny, Y2[k]) - yrr;
        for(int i = X1[k]; i < X2[k]; i++) {
            for(int j = Y1[k]; j < Y2[k]; j++) vst[i][j] = 1;
        }
    }
    
    area.clear();
    for(int i = 0; i < nx; i++) {
        for(int j = 0; j < ny; j++) if(!vst[i][j]) {
            s = 0, vst[i][j] = 1, dfs(i, j);
            area.push_back(s);
        }
    }
    sort(area.begin(), area.end(), [&](int u, int v) {
        return u > v;
    });
    
    int ans = 0;
    for(int i = min(L, (int)area.size()); i--; ) {
        ans += area[i];
    }
    printf("%d\n", ans);
}

int main() {
    int t; scanf("%d", &t);
    while(t--) solve();
    return 0;
}