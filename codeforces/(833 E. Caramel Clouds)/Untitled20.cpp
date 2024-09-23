// LUOGU_RID: 109596598
#include <bits/stdc++.h>

using namespace std;

using u32=unsigned int;
using i64=long long;
using u64=unsigned long long;
using db=double;
using vi=vector<int>;
using pii=pair<int,int>;

template<typename T>
T read(){
    T x=0,f=0;char ch=getchar();
    while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
    while(isdigit(ch)) x=x*10+(ch-'0'),ch=getchar();
    return f?-x:x;
}

#define rdi read<int>
#define rdi64 read<i64>
#define fi first
#define se second
#define pb push_back

const int N=3e5+10,L=N*2;
const int INF=INT_MAX;

int n,W,m;
struct Ban{int l,r,c;}b[N];
int pos[L],tot;
void discrete(){
    pos[tot=1]=0;
    for(int i=1;i<=n;i++)
        pos[++tot]=b[i].l,pos[++tot]=b[i].r;
    sort(pos+1,pos+tot+1),tot=unique(pos+1,pos+tot+1)-pos-1;
    auto rank = [&](int x) {return lower_bound(pos+1,pos+tot+1,x)-pos;};
    for(int i=1;i<=n;i++)
        b[i].l=rank(b[i].l),b[i].r=rank(b[i].r);
}

int mx[L],emp[L];
int v1[N],v2[N],c2[N];

void solve(){
    n=rdi(),W=rdi();
    for(int i=1;i<=n;i++){
        int l=rdi(),r=rdi(),c=rdi();
        b[i]={l,r,c};
    }

    discrete();
    sort(b+1,b+n+1,[&](Ban a,Ban b){
        return a.r<b.r;
    });
        
    static vi a1[L],a2[L];
    for(int i=1;i<=n;i++)
        a1[b[i].l].pb(i),a2[b[i].r].pb(i);

    map<int,int> st;
    auto upd = [&](int c,int v){
        auto it=st.upper_bound(c);
        for(auto it1=it;it1!=st.end()&&it1->se<=v;)
            it1=st.erase(it1);
        it=st.upper_bound(c);
        if(it==st.begin()||prev(it)->se<v)
            st[c]=v;
    };

    set<int> s;
    mx[1]=emp[1]=0;
    for(int i=2;i<=tot;i++){
        int len=pos[i]-pos[i-1];
        for(auto x:a1[i-1]){
            v1[x]=v2[x]=c2[x]=0;
            auto it=st.upper_bound(W-b[x].c);
            if(it!=st.begin()) v2[x]=prev(it)->se;
            s.insert(x);
        }

        mx[i]=mx[i-1],emp[i]=emp[i-1];
        if(s.empty())
            mx[i]+=len,emp[i]+=len;
        else if(s.size()==1){
            int x=*s.begin();
            if(b[x].c<=W){
                v1[x]+=len,v2[x]+=len,c2[x]+=len,upd(b[x].c,v1[x]);
                mx[i]=max(mx[i],emp[i-1]+max(v1[x],v2[x]));
            }
        }
        else if(s.size()==2){
            int x=*s.begin(),y=*next(s.begin());
            c2[x]+=len,c2[y]+=len;
            if(b[x].c+b[y].c<=W){
                v2[y]=max(v2[y],v1[x]+v1[y]+min(c2[x]-v1[x],c2[y]-v1[y]));
                mx[i]=max(mx[i],emp[i-1]+v2[y]);
            }
        }
        for(auto x:a2[i])
            s.erase(x);
    }

    m=rdi();
    for(int i=1;i<=m;i++){
        int k=rdi();
        int p=lower_bound(mx+1,mx+tot+1,k)-mx;
        int ans=(p<=tot?pos[p]-(mx[p]-k):pos[tot]+k-mx[tot]);
        cout<<ans<<'\n';
    }
}

int main(){
#ifdef LOCAL
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
#endif
    solve();
    return 0;
}