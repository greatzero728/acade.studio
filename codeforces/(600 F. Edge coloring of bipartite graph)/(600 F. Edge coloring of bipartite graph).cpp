#include <bits/stdc++.h>
using namespace std;

int main(){
    int a,b,m;
    cin >> a >> b >> m;
    vector<int> A(m + 5), B(m + 5);
    vector<int> d(a + b + 5);
    for(int i = 0;i<m;i++) {
        int u,v;
        cin >> u >> v;
        v +=a;
        A[i] = u;
        B[i] = v;
        d[u]++;
        d[v]++;
    }
    int ans = 0;
    for(int i= 1;i<=a+b;i++) {
        ans = max(ans, d[i]);
    }
    cout << ans << endl;
    int nxt[a + b + 5][ans + 5] = {};
    for(int i = 0;i<m;i++) {
        int u,v;
        u = A[i];
        v = B[i];
        int color1 = 1;
        int color2 = 1;
        while(nxt[u][color1]) color1++;
        while(nxt[v][color2]) color2++;

        nxt[u][color1] = v;
        nxt[v][color2] = u;

        if(color1 == color2) continue;
        
        for(int color = color1,node = v ; node != 0; color = (color == color1 ? color2 : color1), node = nxt[node][color]) {
            swap(nxt[node][color1], nxt[node][color2]);
        }
        
    }
    
    for(int i = 0;i<m;i++) {
        int u,v;
        u = A[i];
        v = B[i];
        for(int color = 1; color <= ans; color++) {
            if(nxt[u][color] == v) {
                cout << color << " ";
                break;
            }
        }
    }
    return 0;
}