#include<bits/stdc++.h>
#define MAX 50005
#define ll long long
#define maxn 5000005
using namespace std;
int n,m,q;
ll C,c[MAX];
int a[MAX],fa[MAX];
vector<int> e[MAX];
int dfn[MAX], cnt, sz[MAX], son[MAX], top[MAX];
void dfs(int now) {
    sz[now] = 1;
    for (auto to : e[now]) {
        dfs(to);
        sz[now] += sz[to];
        if (sz[to] > sz[son[now]]) son[now] = to;
    }
}
void dfs2(int now, int tp) {
    dfn[now] = ++cnt;
    top[now] = tp;
    if (son[now]) dfs2(son[now], tp);
    for (auto to : e[now]) if (to != son[now]) dfs2(to, to);
}
int ls[maxn],rs[maxn],tot;
ll s1[maxn],s2[maxn],tag[maxn];
void ch(int &i,ll tg,int len){
    if(!i) i=++tot;
    s2[i]+=s1[i]*tg+tg*tg*len;
    s1[i]+=2*tg*len;tag[i]+=tg;
}
void pushdown(int i,int l,int r){
    if(tag[i]){
        int mid=(l+r)>>1;
        ch(ls[i],tag[i],mid-l+1);
        ch(rs[i],tag[i],r-mid);
        tag[i]=0;
    }
}
void pushup(int i){
    s1[i]=s1[ls[i]]+s1[rs[i]];
    s2[i]=s2[ls[i]]+s2[rs[i]];
}
void add(int &i,int l,int r,int L,int R,ll tg){
    if(!i) i=++tot;
    if(L<=l&&r<=R){
        ch(i,tg,r-l+1);return;
    }pushdown(i,l,r);int mid=(l+r)>>1;
    if(L<=mid) add(ls[i],l,mid,L,R,tg);
    if(mid<R) add(rs[i],mid+1,r,L,R,tg);
    pushup(i);
}
int rt[MAX];
void insert(int i,int x,ll tg){
    while(top[i]){
        add(rt[x],1,n,dfn[top[i]],dfn[i],tg);
        i=fa[top[i]];
    }
}
ll get(int col,ll sm){
    return n*C*C-sm*C*s1[rt[col]]+sm*sm*s2[rt[col]];
}
int main(){
    scanf("%d%d%d%lld",&n,&m,&q,&C);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=2;i<=n;i++) scanf("%d",&fa[i]),e[fa[i]].push_back(i);
    for(int i=1;i<=m;i++) scanf("%lld",&c[i]);
    dfs(1);dfs2(1,1);
    for(int i=1;i<=n;i++) insert(i,a[i],1);
    for(int i=1,opt,x,y;i<=q;i++){
        scanf("%d%d",&opt,&x);
        if(opt==1){
            scanf("%d",&y);
            insert(x,a[x],-1);a[x]=y;
            insert(x,a[x],1);
        }else printf("%.9Lf\n",1.0L*get(x,c[x])/n);
    }
}