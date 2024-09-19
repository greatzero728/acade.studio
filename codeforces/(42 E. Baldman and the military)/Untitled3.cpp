// LUOGU_RID: 100989960
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+6;
int n,m,q,f[N],U[N],V[N],W[N],de[N];
int p[N],ed[N],w[N],ct,g[N][22],d[N][22];
using ll=long long;
ll Sum;
vector<int>lk[N];
int gf(int x){return x==f[x]?x:f[x]=gf(f[x]);}
void ag(int x,int y,int W){
    int i=++ct;Sum+=w[i+i]=w[i+i+1]=W;
    lk[ed[i+i]=x].push_back(i+i+1);
    lk[ed[i+i+1]=y].push_back(i+i);
}
void dfs(int x=1){
    for(int i=0;g[x][i];++i){
        d[x][i+1]=max(d[x][i],d[g[x][i]][i]);
        g[x][i+1]=g[g[x][i]][i];
    }int y;
    for(int i:lk[x])
        if((y=ed[i])!=g[x][0])
            de[y]=de[x]+1,g[y][0]=x,d[y][0]=w[i],dfs(y);
}
int dis(int x,int y){
    if(de[x]<de[y])swap(x,y);
    int c=de[x]-de[y],k,res=0;
    for(k=18;~k;--k)
        if((c>>k)&1)res=max(res,d[x][k]),x=g[x][k];
    if(x==y)return res;
    for(k=18;~k;--k)
        if(g[x][k]!=g[y][k]){
            res=max({res,d[x][k],d[y][k]});
            x=g[x][k],y=g[y][k];
        }
    res=max({res,d[x][0],d[y][0]});
    return res;
}
int main(){
    ios::sync_with_stdio(false);
    int i,j,k,x,y;
    cin>>n>>m;
    for(x=1;x<=n;++x)f[x]=x;
    for(i=1;i<=m;++i)
        cin>>U[i]>>V[i]>>W[i],p[i]=i;
    sort(p+1,p+m+1,[&](int x,int y){
        return W[x]<W[y];
    });
    for(i=1;i<=m;++i){
        k=p[i],x=gf(U[k]),y=gf(V[k]);
        if(x!=y)f[x]=y,ag(U[k],V[k],W[k]);
    }cin>>q;
    if(ct<n-2){
        while(q--)puts("-1");
    }else if(ct==n-2){
        while(q--){
            cin>>x>>y;
            if(gf(x)==gf(y))puts("-1");
            else printf("%lld\n",Sum);
        }
    }else{
        dfs();
        while(q--){
            cin>>x>>y;
            printf("%lld\n",Sum-dis(x,y));
        }
    }return 0;
}