#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INF 100010001000100010
class SegmentTree {
private:
    vector<ll> tree;
    vector<ll> lazy;
    ll n;

    void build(vector<ll>& arr, ll node, ll start, ll end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            ll mid = (start + end) / 2;
            build(arr, 2 * node + 1, start, mid);
            build(arr, 2 * node + 2, mid + 1, end);
            tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    void updateRangeUtil(ll node, ll start, ll end, ll l, ll r, ll val) {
        if (lazy[node] != 0) {
            // Update current node
            tree[node] += lazy[node];

            // Propagate to children if not a leaf node
            if (start != end) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }

            // Reset the lazy value for current node
            lazy[node] = 0;
        }

        // No overlap condition
        if (start > end || start > r || end < l)
            return;

        // Total overlap condition
        if (start >= l && end <= r) {
            tree[node] += val;
            if (start != end) { // Not a leaf node
                lazy[2 * node + 1] += val;
                lazy[2 * node + 2] += val;
            }
            return;
        }

        // Partial overlap condition
        ll mid = (start + end) / 2;
        updateRangeUtil(2 * node + 1, start, mid, l, r, val);
        updateRangeUtil(2 * node + 2, mid + 1, end, l, r, val);
        tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
    }

    ll queryRangeUtil(ll node, ll start, ll end, ll l, ll r) {
        if (start > end || start > r || end < l)
            return INF; // Out of range

        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (start != end) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (start >= l && end <= r)
            return tree[node];

        ll mid = (start + end) / 2;
        ll left_query = queryRangeUtil(2 * node + 1, start, mid, l, r);
        ll right_query = queryRangeUtil(2 * node + 2, mid + 1, end, l, r);
        return min(left_query, right_query);
    }

public:
    SegmentTree(vector<ll>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(arr, 0, 0, n - 1);
    }

    void update_range(ll l, ll r, ll val) {
        updateRangeUtil(0, 0, n - 1, l, r, val);
    }

    ll query_range(ll l, ll r) {
        return queryRangeUtil(0, 0, n - 1, l, r);
    }
};

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    ll n,q;
    cin>>n>>q;
    ll t1,t2;
    vector<vector<pair<ll,ll>>> adj(n);
    for(ll i=1;i<n;i++)
    {
        cin>>t1>>t2;
        t1--;
        adj[i].push_back({t1,t2});
        adj[t1].push_back({i,t2});
    }
    vector<ll> isLeaf(n);
    vector<ll> dis(n,INF);
    vector<ll> till(n);
    dis[0]=0;
    ll count=0;
    function <void(ll,ll)> dfs= [&](ll node,ll parent){
        if(adj[node].size()==1){
            isLeaf[node]=1;
        }
        for(auto i: adj[node])
        {
            count=max(count,i.first);
            if(i.first==parent)continue;
            dis[i.first]=dis[node]+i.second;
            dfs(i.first,node);
        }
        till[node]=count;
        
    };
    dfs(0,-1);
    for(ll i=0;i<n;i++){
        if(isLeaf[i]==0)dis[i]=INF;
    }
    SegmentTree seg(dis);
    map <ll,vector<vector<ll>>>query;
    for(ll i=0;i<q;i++)
    {
        ll nd, le, r;
        cin>>nd>>le>>r;
        nd--;le--;r--;
        vector<ll> v(3);
        v[0]=le;v[1]=r;v[2]=i;
        query[nd].push_back(v);
    }   
    vector<ll> ans(q);
    function <void(ll,ll)> dfs2=[&](ll node,ll parent){
        for(auto i:query[node]){
            ans[i[2]]=seg.query_range(i[0],i[1]);
        }
        for(auto i:adj[node]){
            if(i.first==parent)continue;
            seg.update_range(i.first,till[i.first],-i.second);
            seg.update_range(0,i.first-1,i.second);
            seg.update_range(till[i.first]+1,n-1,i.second);
            dfs2(i.first,node);
            seg.update_range(i.first,till[i.first],i.second);
            seg.update_range(0,i.first-1,-i.second);
            seg.update_range(till[i.first]+1,n-1,-i.second);
        }

    };
    dfs2(0,-1);
    for(ll i=0;i<q;i++)cout<<ans[i]<<endl;
}