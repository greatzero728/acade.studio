#include<bits/stdc++.h>

using namespace std;

const int NN = 202020;

int a[NN], b[NN >> 1];

int main() {
    int n; scanf("%d", &n);
    for(int i = 1; i <= n >> 1; i++) scanf("%d", b + i);
    
    a[n] = b[1];
    for(int i = 2; i <= n >> 1; i++) {
        INT st = b[i] >> 1, ed = b[i] - st;
        INT len = min(st - a[i - 1], a[n - i + 2] - ed);
        a[i] = st - len, a[n - i + 1] = b[i] - a[i];
    }
    
    for(int i = 1; i <= n; i++) printf("%d ", a[i]);
}