#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

// Step 2: Implement and manage DSU
struct DSU
{
    vector<int> parent;

    DSU(int n) : parent(n)
    {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int v)
    {
        if (parent[v] != v)
        {
            parent[v] = find(parent[v]);
        }
        return parent[v];
    }

    void unite(int u, int v)
    {
        parent[find(u)] = find(v);
    }

    bool connected(int u, int v)
    {
        return find(u) == find(v);
    }
};


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Step 1: Read input and initialize variables

    string s;
    cin >> s;

    int m = s.length();
    int tot = 0;
        
    // Step 2.1: Iterate over possible split points
    for (int i = 1; i < m; ++i)
    {
        // Step 2.2: Initialize segment indices for disjoint set
        vector<array<int, 2>> ds(m), dt(m);
        int idc = 0;

        for (int j = 0; j < m; ++j)
        {
            dt[j][0] = idc++;
            dt[j][1] = idc++;
        }
        for (int j = i; j < m; ++j)
        {
            ds[j][0] = idc++;
            ds[j][1] = idc++;
        }
        
        // Step 2.3: Create and initialize DSU for the current split point
        DSU dsu(idc);
        
        
        // Step 2.4: Merge disjoint sets based on palindromic constraints
        for (int l = 0, r = m - 1; l < r; ++l, --r)
        {
            dsu.unite(dt[l][0], dt[r][0]);
            dsu.unite(dt[l][1], dt[r][1]);
        }
        for (int l = i, r = m - 1; l < r; ++l, --r)
        {
            dsu.unite(ds[l][0], ds[r][0]);
            dsu.unite(ds[l][1], ds[r][1]);
        }
        
        // Step 2.5: Process the input string to merge sets based on constraints
        for (int j = i; j < m; ++j)
        {
            if (s[j] != '?')
            {
                int bit = s[j] - '0';
                dsu.unite(ds[j][0], dt[j][bit]);
                dsu.unite(ds[j][1], dt[j][bit ^ 1]);
            }
        }
        
         // Step 3: Calculate the number of valid pairs
        int ans = 1;
        for (int j = 0; j < idc; j += 2)
        {
            if (dsu.connected(j, j + 1))
            {
                ans = 0;
            }
        }
        
        // Step 3.1: Track selected sets for the first part of the string
        vector<int> sel(idc, 0);
        for (int j = 0; j < i; ++j)
        {
            if (s[j] != '?')
            {
                sel[dsu.find(dt[j][s[j] - '0'])] = 1;
            }
        }
        sel[dsu.find(ds[i][1])] = 1;
        
        // Step 3.2: Update the answer based on set selections
        for (int j = 0; j < idc; j += 2)
        {
            if (dsu.find(j) == j)
            {
                if (sel[j] && sel[j + 1])
                {
                    ans = 0;
                }
                else if (!sel[j] && !sel[j + 1])
                {
                    ans = ans * 2LL % MOD;
                }
            }
        }

        tot = (tot + ans) % MOD;
    }
    
    // Step 4: Output the final result
    cout << tot << '\n';

    return 0;
}
