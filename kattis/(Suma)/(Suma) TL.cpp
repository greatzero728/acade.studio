#include <bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = long long;
using pii = pair<int, int>;

const int NN = 707, MM = NN * NN;

int h[NN][NN], v[NN][NN];
int id[NN][NN], nn;
pii pos[MM];
int rt[MM], original_rt[MM];
pii updatedIndex[MM * 100];
int mm;

int find(int u) {
    if(rt[u] < 0) return u;
    int updated_rt = find(rt[u]);
    updatedIndex[mm++] = {u, rt[u]};
    return rt[u] = updated_rt;
}

map<pii, vector<pii>> events;

void update(int a, int b) {
    int ha = h[pos[a].x][pos[a].y], va = v[pos[a].x][pos[a].y];
    int hb = h[pos[b].x][pos[b].y], vb = v[pos[b].x][pos[b].y];
    
    if(ha == hb) {
        if(va == vb) {
            a = find(a), b = find(b);
            if(a != b) {
                rt[a] += rt[b];
                rt[b] = a;
            }
        }
        else events[{0, 1}].push_back({a, b});
    }
    else if(ha < hb) {
        if(va > vb) {
            int tu = hb - ha, td = va - vb, g = __gcd(tu, td);
            events[{tu / g, td / g}].push_back({a, b});
        }
    }
    else {
        if(va < vb) {
            int tu = ha - hb, td = vb - va, g = __gcd(tu, td);
            events[{tu / g, td / g}].push_back({a, b});
        }
    }
}

int main() {
    int N; scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            scanf("%d", h[i] + j);
            
            id[i][j] = ++nn;
            pos[nn] = {i, j};
            rt[nn] = -1;
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            scanf("%d", v[i] + j);
            
            if (i > 1) update(id[i][j], id[i - 1][j]);
            if (j > 1) update(id[i][j], id[i][j - 1]);
        }
    }
    
    int maxSize = -*min_element(rt + 1, rt + nn + 1);
    for(auto vec : events) {
        for(pii p : vec.y) {
            int a = find(p.x), b = find(p.y);
            if(a != b) {
                if(-rt[a] < -rt[b]) swap(a, b);
                updatedIndex[mm++] = {a, rt[a]};
                rt[a] += rt[b];
                maxSize = max(maxSize, -rt[a]);
                
                updatedIndex[mm++] = {b, rt[b]};
                rt[b] = a;
            }
        }
        while(mm) {
            mm--;
            rt[updatedIndex[mm].x] = updatedIndex[mm].y;
        }
    }
    printf("%d\n", maxSize);
}