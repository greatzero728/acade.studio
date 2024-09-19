#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using pii = pair<int, int>;

int p[5], a[5];

int main() {
    int n, k; scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i++) scanf("%d", p + i);
    
    vector<pii> vec;
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++) vec.push_back({i, j});
    }
    
    int num = 0;
    for(int s = pow(vec.size(), k); s--; ) {
        for(int i = 1; i <= n; i++) a[i] = p[i];
        for(int i = k, c = s; i--; c /= vec.size()) {
            int L = vec[c % vec.size()].x, R = vec[c % vec.size()].y;
            cout<<L<<' '<<R<<endl;
            reverse(a + L, a + R + 1);
        }
        puts("==========================");
        for(int j = 2; j <= n; j++) {
            for(int i = 1; i < j; i++) if(a[i] > a[j]) num++;
        }
    }
    printf("%.15lf\n", num / pow(vec.size(), k));
}