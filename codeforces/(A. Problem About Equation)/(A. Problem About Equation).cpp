#include<bits/stdc++.h>

using namespace std;
using DO = double;

const int NN = 121;

DO a[NN], b;

int main() {
    
    int n; scanf("%d %lf", &n, &b);
    for(int i = 1; i <= n; i++) scanf("%lf", a + i);
    
    DO totalAmount = b;
    for(int i = 1; i <= n; i++) totalAmount += a[i];
    
    DO finalAmountOfEachMug = totalAmount / n;
    
    for(int i = 1; i <= n; i++) if(a[i] > finalAmountOfEachMug) {
        puts("-1"); return 0;
    }
}