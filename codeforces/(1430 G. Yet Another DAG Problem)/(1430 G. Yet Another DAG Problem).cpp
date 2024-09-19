#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9, NN = 18;

int n, m;
int dp[1 << NN];  // dp[mask] - minimum cost for a set of vertices
int sum[1 << NN]; // sum[mask] - sum of cost[v] for vertices in the mask
int cost[NN];     // cost[v] = outgoing_sum(v) - incoming_sum(v)
int nxt[NN];      // nxt[v] - bitmask of vertices reachable from v
int prv[NN];      // prv[v] - bitmask of vertices that can reach v
int rev[1 << NN]; // to track the set of vertices added to each state
int ans[NN];      // to store the final answer for each vertex

int main() {

    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w; scanf("%d %d %d", &u, &v, &w);
        u--; v--; // 0-indexed
        nxt[u] |= (1 << v); // v is reachable from u
        prv[v] |= (1 << u); // u can reach v
        cost[u] += w;       // out-sum for u
        cost[v] -= w;       // in-sum for v
    }

    // Precompute sum for each subset of vertices (bitmask)
    for (int mask = 0; mask < 1 << n; mask++) {
        sum[mask] = 0;
        for (int i = 0; i < n; i++) {
			if (mask & (1 << i)) sum[mask] += cost[i];
        }
    }

    // Initialize DP
    dp[0] = 0; // base case: no vertices selected

    // Iterate over all masks (states)
    for (int mask = 1; mask < 1 << n; mask++) {
    	dp[mask] = inf;
        int available = 0, valid = 1;
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                // Store all rechable vertices from i to available
                if ((nxt[i] & mask) == 0) available |= 1 << i;
                // Check if the mask contains vertices that can reach i
                if ((prv[i] & mask) != prv[i]) valid = 0;
            }
        }
        
        if (!valid) continue; // skip invalid states

        // Iterate over all subsets of 'available' vertices
        for (int submask = available; submask; submask = (submask - 1) & available) {
            if (dp[mask] > dp[mask ^ submask] + sum[mask ^ submask]) {
                dp[mask] = dp[mask ^ submask] + sum[mask ^ submask];
                rev[mask] = submask; // record the subset used to transition
            }
        }
    }

    // Reconstruct the solution
    int current_mask = (1 << n) - 1; // all vertices
    int value = 0;

    while (current_mask) {
        int used_set = rev[current_mask];
        for (int i = 0; i < n; i++) {
            if ((used_set >> i) & 1) {
                ans[i] = value; // assign current value to vertex i
            }
        }
        value++;
        current_mask ^= used_set; // remove used vertices from the mask
    }

    // Output the answer
    for (int i = 0; i < n; i++) printf("%d ", ans[i]);

    return 0;
}
