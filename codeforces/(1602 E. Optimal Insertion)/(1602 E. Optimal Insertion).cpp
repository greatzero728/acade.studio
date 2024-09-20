#include<bits/stdc++.h>

using namespace std;
using INT = long long;

int n, m;

const int NN = 1010101;

int a[NN], b[NN], arr[NN << 1], nn;
int B[NN << 1];

void update(int u) {
    for(; u; u ^= u & -u) B[u]++;
}
int calc(int u) {
    int ans = 0;
    for(; u <= nn; u += u & -u) ans += B[u];
    return ans;
}

int pos[NN];

void solve(int L, int R, int st, int ed) {
    int md = st + ed >> 1;
    pos[md] = L - 1;
    int inv = 0, mn = 0;
    for(int i = L; i <= R; i++) {
        if(b[md] < a[i]) inv++;
        if(b[md] > a[i]) inv--;
        if(inv < mn) mn = inv, pos[md] = i;
    }
    if(st < md) solve(L, pos[md], st, md - 1);
    if(md < ed) solve(pos[md], R, md + 1, ed);
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        
        nn = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            arr[nn++] = a[i];
        }
        for(int i = 1; i <= m; i++) {
            scanf("%d", b + i);
            arr[nn++] = b[i];
        }
        
        sort(arr, arr + nn);
        nn = unique(arr, arr + nn) - arr;
        
        for(int i = 1; i <= n; i++) {
            a[i] = upper_bound(arr, arr + nn, a[i]) - arr;
        }
        
        sort(b + 1, b + m + 1);
        for(int i = 1; i <= m; i++) {
            b[i] = upper_bound(arr, arr + nn, b[i]) - arr;
        }
        
        solve(1, n, 1, m);
        
        INT ans = 0;
        for(int i = 1; i <= nn; i++) B[i] = 0;
        for(int i = 0, mm = 1; i <= n; i++) {
            if(i) {
                update(a[i]);
                ans += calc(a[i] + 1);
            }
            for(;mm <= m && pos[mm] == i; mm++) {
                update(b[mm]);
                ans += calc(b[mm] + 1);
            }
        }
        cout<<ans<<endl;
    }
}