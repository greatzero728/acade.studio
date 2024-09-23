#include<bits/stdc++.h>
#define LL long long
#define LLL __int128
#define uint unsigned
#define ldb long double
#define uLL unsigned long long
using namespace std;
const int N=6e5+5,INF=2e9;
int n,m,C,V;
set<int>S;
pair<int,int>Q[N];
tuple<int,int,int>A[N];
map<pair<int,int>,int>mp;
int B[N],ans[N],f[N],g[N],T[N*2];
inline void upd(int p,int l,int r,int x,int y){
    if(l==r)return T[p]+=y,void();
    const int mid=(l+r)>>1,ls=p*2,rs=p*2+1;
    x<=mid?upd(ls,l,mid,x,y):upd(rs,mid+1,r,x,y);
    T[p]=max(T[ls],T[rs]);
}
inline int qry(int p,int l,int r,int x){
    if(r<=x)return T[p];
    const int mid=(l+r)>>1,ls=p*2,rs=p*2+1;
    return x<=mid?qry(ls,l,mid,x):max(T[ls],qry(rs,mid+1,r,x));
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
#define LOCAL
#ifndef LOCAL
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
#endif
    cin>>n>>C;
    for(int i=1,l,r,c;i<=n;++i)
        cin>>l>>r>>c,A[i]=make_tuple(c,l,r),B[i]=l,B[i+n]=r;
    sort(A+1,A+n+1),sort(B+1,B+n+n+2),V=unique(B+1,B+n+n+2)-B-1,B[V+1]=INF;
    for(int i=1;i<=n;++i)Q[i]=make_pair(get<1>(A[i]),i),Q[i+n]=make_pair(get<2>(A[i]),-i);
    sort(Q+1,Q+n+n+1);
    for(int i=1,j=1,k=0,cur=0;i<=V;++i){
        for(;j<=n+n&&Q[j].first<=B[i];++j)
            if(Q[j].second>0)S.emplace(Q[j].second);
            else S.erase(-Q[j].second);
        if(S.empty())k+=B[i+1]-B[i];
        else if(S.size()==1){
            int x=*S.begin();
            if(get<0>(A[x])<=C){
                int p=lower_bound(A+1,A+n+1,make_tuple(C-get<0>(A[x])+1,-1,-1))-A-1;
                upd(1,1,n,x,-f[x]);
                if(p)g[x]=max(g[x],qry(1,1,n,p));
                f[x]+=B[i+1]-B[i];
                upd(1,1,n,x,f[x]);
                cur=max(cur,f[x]+g[x]);
            }
        }
        else if(S.size()==2){
            int x=*S.begin(),y=*S.rbegin();
            if(get<0>(A[x])+get<0>(A[y])<=C){
                int z=(mp[{x,y}]+=B[i+1]-B[i]);
                g[x]=max(g[x],f[y]+z),g[y]=max(g[y],f[x]+z);
                cur=max(cur,f[x]+f[y]+z);
            }
        }
        ans[i]=k+cur;
    }
    cin>>m;
    for(int i=1,x;i<=m;++i){
        cin>>x;
        int y=lower_bound(ans+1,ans+V+1,x)-ans;
        cout<<B[y+1]-ans[y]+x<<'\n';
    }
    return 0;
}
/*
 
*/ 