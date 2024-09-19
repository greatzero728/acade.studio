#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
typedef long long ll;
map<ll,ll>mp;
ll LCA(ll u,ll v,ll w){
    ll ans=0;
    while(u!=v){
        if(u<v) swap(u,v);
        mp[u]+=w,ans+=mp[u];
        u>>=1;
    }
    return ans;
}
int main(){
    int q;scanf("%d",&q);
    while(q--){
        ll f,u,v,w;cin>>f>>u>>v;
        if(f==1) cin>>w,LCA(u,v,w);
        else cout<<LCA(u,v,0)<<endl;
    }
}