#include<bits/stdc++.h>

using namespace std;
using INT = long long;

const int NN = 101010, MM = 202020;

int t[NN], nn = 1;
INT l[NN], r[NN];
INT arr[MM] = {1};

int main() {
    int n; scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d %lld %lld", t + i, l + i, r + i), r[i]++;
        arr[nn++] = l[i], arr[nn++] = r[i];
    }
    sort(arr, arr + nn);
    nn = unique(arr, arr + nn) - arr;
    
    bitset<MM> flag, all;
    flag.flip(), all.flip();
    
    for(int i = 1; i <= n; i++) {
        l[i] = lower_bound(arr, arr + nn, l[i]) - arr;
        r[i] = lower_bound(arr, arr + nn, r[i]) - arr;
        
        // all >> MM - (r[i] - l[i]) is the bitset that has exactly r[i] - l[i] ones at the beginning
        // we can move above ones to the corresponding position, and this is final bitset tmp: all >> MM - (r[i] - l[i]) << l[i]
        if(t[i] == 1) flag &= ~(all >> MM - (r[i] - l[i]) << l[i]);
        else if(t[i] == 2) flag |= all >> MM - (r[i] - l[i]) << l[i];
        else flag ^= all >> MM - (r[i] - l[i]) << l[i];
        
        printf("%lld\n", arr[flag._Find_first()]);
    }
}