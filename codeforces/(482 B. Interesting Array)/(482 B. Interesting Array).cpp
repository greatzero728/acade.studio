#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
ll pref[30][N];
int query(int j , int l , int r) {
    return pref[j][r] - (l == 0 ? 0 : pref[j][l - 1]);
}
int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n , m;
    cin>>n>>m;
    vector<array<int , 3>>queries;
    for(int i = 0;i < m;i++) {
        int l , r , q;cin>>l>>r>>q;
        queries.emplace_back(array<int , 3>{l , r, q});
        for(int j = 0;j < 30;j++) {
            if(q & (1LL << j)) {
                pref[j][l - 1]++ , pref[j][r]--;
            }
        }
    }
    for(int i = 1;i < n;i++) {
        for(int j = 0;j < 30;j++) {
            pref[j][i] += pref[j][i - 1];
        }
    }
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < 30;j++) {
            pref[j][i] = min(1ll , pref[j][i]);
        }
    }
    for(int i = 1;i < n;i++) {
        for(int j = 0;j < 30;j++) {
            pref[j][i] += pref[j][i - 1];
        }
    }
    // for(int i = 0;i < n;i++)cout<<pref[0][i]<<" "<<pref[1][i]<<endl;

    for(int i = 0;i < m;i++) {
        auto [l ,r , q] = queries[i];
        for(int j = 0;j < 30;j++) {
            if(!(q & (1LL<<j))) {
                if(query(j , l - 1, r - 1) == r - l  + 1) {
                    cout<<"NO";
                    exit(0);
                }
            }
        }
    }
    cout<<"YES"<<'\n';
    for(int i = 0;i < n;i++) {
        ll res = 0;
        for(int j = 0;j < 30;j++) {
            res |= (1<<j) * query(j , i , i);
        }
        cout<<res<<" ";
    }
}