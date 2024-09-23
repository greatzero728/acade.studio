#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n,q;
    cin>>n>>q;
    map<int,pair<char,ll>>mp;
    mp[0]={'U',0};
    mp[n+1]={'L',0};
    while(q--){
        int y,x;
        char dir;
        cin>>y>>x>>dir;
        auto it=mp.lower_bound(x);
        if(it->first==x){
            cout<<0<<endl;
            continue;
        }
        if(dir=='U'){
            it--;
        }
        ll ans=abs(x-it->first);
        if(it->second.first==dir){
            ans+=(it->second.second);
        }
        mp[x]={dir,ans};
        cout<<ans<<endl;
    }
}