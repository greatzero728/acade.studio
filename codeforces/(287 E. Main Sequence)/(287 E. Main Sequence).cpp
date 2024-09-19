#include <bits/stdc++.h>
using namespace std;

const int NN = 1010101;

int p[NN], tp[NN];

int main() {
    int n; scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", p + i);
        tp[i] = 1;
    }
    int t; scanf("%d", &t);
    while(t--) {
        int x; scanf("%d", &x);
        tp[x] = -1;
    }
    stack<int> s;
    for(int i = n; i; i--) {
        if(tp[i] == -1) s.push(p[i]);
        else if(s.empty()) {
            tp[i] = -1, s.push(p[i]);
        }
        else if(s.top() == p[i]) s.pop(); //We found a valid minimum bracket pair
        else puts("NO"), exit(0); //We found that our sequence is not valid.
    }
    
    if(s.empty()) {
        puts("YES");
        for(int i = 1; i <= n; i++) printf("%d ", tp[i] * p[i]);
    }
    else puts("NO");
    return 0;
}