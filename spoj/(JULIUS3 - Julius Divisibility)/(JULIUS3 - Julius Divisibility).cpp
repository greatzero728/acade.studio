#include "bits/stdc++.h"
using namespace std;

void solve()
{
    int n; cin>>n;
    vector<int> v(n);
    for(int i=0;i<n;i++) cin>>v[i];
    int cnt0=0,cnt5=0;
    for(int i=0;i<n;i++)
    {
        cnt0+=(v[i]==0);
        cnt5+=(v[i]==5);
    }
    if(!cnt0)
    {
        cout<<-1;
    }
    else
    {
        int tot_5=(cnt5/9)*9;
        int tot_0=cnt0;
        if(tot_5==0)
        {
            cout<<0<<endl;
            return;
        }
        while(tot_5--) cout<<5;
        while(tot_0--) cout<<0;
    }  
    cout<<endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc; cin>>tc;
    while(tc--) solve();
    return 0;
}