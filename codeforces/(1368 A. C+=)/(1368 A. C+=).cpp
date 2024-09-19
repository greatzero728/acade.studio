#include<bits/stdc++.h>

using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int a, b, n; scanf("%d %d %d", &a, &b, &n);
        int ans = 0;
        while(a <= n && b <= n) {
            if(a > b) {
                b += a;
            } else {
                a += b;
            }
            ans++;
        }
        printf("%d\n", ans);
    }
}