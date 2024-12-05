#include <bits/stdc++.h>

using namespace std;
using INT = long long;

const int NN = 1010101;

INT Qi[NN];

int main() {
    int N, Q; scanf("%d %d", &N, &Q);
    for(int i = 1; i <= N; i++) scanf("%lld", Qi + i);
    
    INT maximumGreaterThanQ = 1e13;
    for(int i = 1; i <= N; i++) if(Qi[i] > Q) {
        maximumGreaterThanQ = min(maximumGreaterThanQ, Qi[i]);
    }
    printf("%lld\n", maximumGreaterThanQ);
    return 0;
}