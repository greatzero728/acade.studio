#include <bits/stdc++.h>

using namespace std;
using INT = long long;

const int mod = 1e9 + 7;

int power(int a, int b) {
    int ans = 1;
    for(; b; b >>= 1, a = (INT)a * a % mod) {
        if(b & 1) ans = (INT)ans * a % mod;
    }
    return ans;
}

const int NN = 404040, inv_2 = power(2, mod - 2);

int rt[NN], ans;
set<int> Set[NN][2];
int color[NN][2];

int nn;
map<int, int> mp;

int id(int x) {
    if(mp.find(x) == mp.end()) {
        mp[x] = nn;
        rt[nn] = nn;
        color[nn][0] = -1, Set[nn][0].clear();
        color[nn][1] = -1, Set[nn][1].clear(), Set[nn][1].insert(nn);
        nn++;
    }
    return mp[x];
}

int find(int u) {
    return rt[u] == u ? u : rt[u] = find(rt[u]);
}

int get_index(int rt, int u) {
    return Set[rt][1].find(u) != Set[rt][1].end();
}

void add(int rt_a, int a, int rt_b, int b, string flag) {
    if(!ans) return;
    int pos_a = get_index(rt_a, a);
    int pos_b = get_index(rt_b, b);
    int sz_a = Set[rt_a][0].size() + Set[rt_a][1].size();
    int sz_b = Set[rt_b][0].size() + Set[rt_b][1].size();
    int RT, POS;
    int rt, pos;
    
    if(sz_a > sz_b) {
        RT = rt_a, POS = pos_a, rt = rt_b, pos = pos_b;
    }
    else {
        RT = rt_b, POS = pos_b, rt = rt_a, pos = pos_a;
    }
    
    if(flag == "same") {
        if(rt_a == rt_b) {
            if(pos_a != pos_b) ans = 0;
        }
        else {
            if(~color[rt_a][pos_a] && ~color[rt_b][pos_b]) {
                if(color[rt_a][pos_a] != color[rt_b][pos_b]) ans = 0;
            }
            else {
                if(POS == pos) {
                    for(int i = 2; i--; ) {
                        for(int x : Set[rt][i]) Set[RT][i].insert(x);
                        if(~color[rt][i]) color[RT][i] = color[rt][i];
                    }
                }
                else {
                    for(int i = 2; i--; ) {
                        for(int x : Set[rt][i]) Set[RT][i ^ 1].insert(x);
                        if(~color[rt][i]) color[RT][i ^ 1] = color[rt][i];
                    }
                }
                ::rt[rt] = RT;
                ans = (INT)ans * inv_2 % mod;
            }
        }
    }
    else {
        if(rt_a == rt_b) {
            if(pos_a == pos_b) ans = 0;
        }
        else {
            if(~color[rt_a][pos_a] && ~color[rt_b][pos_b]) {
                if(color[rt_a][pos_a] == color[rt_b][pos_b]) ans = 0;
            }
            else {
                if(POS != pos) {
                    for(int i = 2; i--; ) {
                        for(int x : Set[rt][i]) Set[RT][i].insert(x);
                        if(~color[rt][i]) color[RT][i] = color[rt][i];
                    }
                }
                else {
                    for(int i = 2; i--; ) {
                        for(int x : Set[rt][i]) Set[RT][i ^ 1].insert(x);
                        if(~color[rt][i]) color[RT][i ^ 1] = color[rt][i];
                    }
                }
                ::rt[rt] = RT;
                ans = (INT)ans * inv_2 % mod;
            }
        }
    }
}

void replace(int rt, int u, int x) {
    if(!ans) return;
    int pos = get_index(rt, u);
    if(~color[rt][pos]) {
        if(color[rt][pos] != x) ans = 0;
        return;
    }
    color[rt][pos] = x;
    color[rt][pos ^ 1] = x ^ 1;
    ans = (INT)ans * inv_2 % mod;
}

int main() {
    int N, M; scanf("%d %d", &N, &M);
    ans = power(2, N);
    while(M--) {
        int tp, A, B; scanf("%d %d %d", &tp, &A, &B);
        int Root_A = find(A = id(A));
        int Root_B = find(B = id(B));

        if(tp == 1) {
            add(Root_A, A, Root_B, B, "same");
        }
        else if(tp == 2) {
            add(Root_A, A, Root_B, B, "diff");
        }
        else if(tp == 3) {
            replace(Root_B, B, 1);
        }
        else {
            replace(Root_B, B, 0);
        }
        printf("%d\n", ans);
    }
}