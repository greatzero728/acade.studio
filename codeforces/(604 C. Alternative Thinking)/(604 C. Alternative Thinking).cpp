#include<bits/stdc++.h>

using namespace std;

int a[101010];

int main() {
    int n; scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", a + i);
    
    int ans = 2;
    for(int i = 1; i < n; i++) if(a[i] ^ a[i + 1]) ans++;
    printf("%d\n", min(ans, n));
}