#include<bits/stdc++.h>

using namespace std;

int main() {
    int n, s; scanf("%d %d", &n, &s);
    vector<int> a(n, 0);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    sort(a.begin(), a.end());
    
    int sum = 0;
    for(int i = 0; i < a.size() - 1; i++) sum += a[i];
    if(sum <= s) puts("YES");
    else puts("NO");
}