#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
int n, k;
int a[MAXN];

int main() {

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    long long s = 0, num = 0;
    for (int i = 1; i <= n; i++) {
        if(s - (i - num - 1) * (n - i) * a[i] < k) cout<<i<<endl, num++;
        else s += a[i] * (i - num - 1);
    }

    return 0;
}