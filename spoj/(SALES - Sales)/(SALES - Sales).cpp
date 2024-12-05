#include <bits/stdc++.h>
#define y second
#define x first

using namespace std;
using pii = pair<int, int>;

const int NN = 51, MM = 30001;

int c[MM], v[MM];
vector<int> pq[NN];
vector<pii> vec;
int dp[NN], next_dp[NN];

int main() {
    int B, N, D; scanf("%d %d %d", &B, &N, &D);
    
    for(int i = 1; i <= N; i++) scanf("%d %d", c + i, v + i);
    
    while(D--) {
        int a, b, x, y; scanf("%d %d %d %d", &a, &b, &x, &y);
        
        c[a] = b;
        
        for(int i = 1; i <= B; i++) pq[i].clear();
        
        for(int i = x; i <= y; i++) {
            if(c[i] <= B) pq[c[i]].push_back(v[i]);
        }
        
        vec.clear();
        for(int i = 1; i <= B; i++) {
            int max_num = B / i;
            if (pq[i].size() > max_num) {
                nth_element(pq[i].begin(), pq[i].begin() + max_num, pq[i].end(), greater<int>());
                pq[i].resize(max_num);
            }
            for (int val : pq[i]) vec.push_back({i, val});
        }
        
        for(int i = 0; i <= B; i++) dp[i] = 0;
        for(pii p: vec) {
            int C = p.x, P = p.y;
            
            for(int i = 0; i <= B; i++) next_dp[i] = dp[i];
            for(int i = 0; i <= B; i++) if(i + C <= B) {
                next_dp[i + C] = max(next_dp[i + C], dp[i] + P);
            }
            for(int i = 0; i <= B; i++) dp[i] = next_dp[i];
        }
        
        printf("%d\n", dp[B]);
    }
}
