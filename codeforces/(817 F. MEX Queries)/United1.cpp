#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fi first
#define se second
map<ll,ll>s;
void sp(ll p){
    auto it=prev(s.upper_bound(p));
    s[p]=it->se;
}
void cov(ll l,ll r,int x){
    sp(l),sp(r+1);
    auto it=s.find(l);
    while(it->fi!=r+1)it=s.erase(it);
    s[l]=x;
}
void rev(ll l,ll r){
    sp(l),sp(r+1);
    auto it=s.find(l);
    while(it->fi!=r+1){
        it->se^=1;
        ++it;
    }
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    int q;
    cin>>q;
    s[1]=0;
    while(q--){
        ll op,l,r;
        cin>>op>>l>>r;
        if(op==1)cov(l,r,1);
        else if(op==2)cov(l,r,0);
        else rev(l,r);
        auto it=s.begin();
        while(it->se)++it;
        cout<<it->fi<<'\n';
    }
}