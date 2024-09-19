#include <bits/stdc++.h>
using namespace std;
const string dl = "\n";
typedef long long ll;
//#define all(v) v.begin(), v.end()

vector<int> get_top_sort(vector<vector<pair<ll, ll>>> adj)
{
    int n = adj.size();
    n--;
    vector<bool> visited(n + 10, 0);
    vector<int> top_sort;
    function<void(int)> dfs = [&](int v)
    {
        visited[v] = true;
        for (auto [u, w] : adj[v])
        {
            if (!visited[u])
                dfs(u);
        }
        top_sort.push_back(v);
    };
    for (int i = 1; i <= n; ++i)
    {
        if (!visited[i])
            dfs(i);
    }
    reverse(top_sort.begin(), top_sort.end());
    return top_sort;
}


vector<vector<pair<ll, ll>>> get_reverse_graph(vector<vector<pair<ll, ll>>> adj)
{
    int n = adj.size();
    n--;
    vector<vector<pair<ll, ll>>> rev(n + 1);
    for (int i = 1; i <= n; i++)
    {
        for (auto [u, w] : adj[i])
        {
            rev[u].push_back({i, w});
        }
    }
    return rev;
}


void solve()
{
    ll n, m;
    cin >> n >> m;
    vector<vector<pair<ll, ll>>> adj(n + 10);
    for (int i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    auto top_sort = get_top_sort(adj);
    
    
    vector<bool> vis(n + 10, false);
    vector<ll> dist(n + 10, 0), gcd(n + 10, 0), comp(n + 10, 0);
    int cur_comp = 1;


    adj = get_reverse_graph(adj);

    
    function<void(int)> dfs = [&](int u)
    {
        vis[u] = true;
        for (auto [v, w] : adj[u])
        {
            if (!vis[v])
            {
                dist[v] = dist[u] + w;
                comp[v] = comp[u];
                dfs(v);
            }
            else if (comp[u] == comp[v])
                gcd[comp[u]] = __gcd(gcd[comp[u]], abs(dist[u] + w - dist[v]));
        }
    };

    for (auto &u : top_sort)
    {
        if (!vis[u])
        {
            comp[u] = cur_comp, dist[u] = 0;
            dfs(u);
            cur_comp++;
        }
    }

    
    
    ll q;
    cin >> q;
    while (q--)
    {
        ll u, s, t;
        cin >> u >> s >> t;
        
        ll g = __gcd(gcd[comp[u]], t);
        if (g and s % g)
            cout << "NO" << dl;
        else
            cout << "YES" << dl;
    }
}

int main()
{

    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    solve();
    return 0;
}