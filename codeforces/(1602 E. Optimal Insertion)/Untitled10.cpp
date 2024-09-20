#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5;
int a[N],b[N],p[N];
int M,c[N+N],num[N+N],tr[N+N];
void add(int x,int y){
    for(;x;x-=x&-x)tr[x]+=y;
}
int query(int x){
    int res=0;
    for(;x<N+N;x+=x&-x)res+=tr[x];
    return res;
}
void solve(int l,int r,int L,int R){
    if(l>r)return;
    int mid=(l+r)/2,res=0,sum=0,pos=L;
    for(int i=L+1;i<=R;i++){
        if(a[i-1]>b[mid])sum++;
        if(a[i-1]<b[mid])sum--;
        if(res>sum)res=sum,pos=i;
    }
    p[mid]=pos,solve(l,mid-1,L,pos),solve(mid+1,r,pos,R);
}
void solve(){
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=m;i++)cin>>b[i];
    sort(b+1,b+m+1);
    solve(1,m,1,n+1);
    M=0;
    for(int i=1,j=1;i<=n+1;i++){
        while(j<=m&&p[j]<=i)c[++M]=b[j++];
        if(i<=n)c[++M]=a[i];
    }
    for(int i=1;i<=M;i++)num[i]=c[i];
    sort(num+1,num+M+1);
    ll ans=0;
    for(int i=1;i<=M;i++){
        int x=lower_bound(num+1,num+M+1,c[i])-num;
        ans+=query(x+1);add(x,1);
    }
    for(int i=1;i<=M;i++)tr[i]=0;
    cout<<ans<<'\n';
}
int main(){
    cin.tie(0);ios::sync_with_stdio(0);cout.tie(0);
    int T;cin>>T;while(T--)solve();
}