#include <stdio.h>
typedef long long ll;
ll max(ll a,ll b){return a<b?b:a;}
ll w[100005],bit[(1<<17)+5];
int a[100005],n;
int f(int x){ return x&-x;}
void update(int i,ll x){ for(int s=i;s<=(1<<17);s+=f(s)) bit[s]=max(bit[s],x);}
ll get(int i){ ll ret=0LL; for(int s=i;s>0;s-=f(s)) ret=max(ret,bit[s]); return ret;}
int main()
{
  scanf("%d",&n);
  for(int i=1;i<=n;i++) w[i]=i;
  for(int i=1;i<=n;i++) scanf("%d",&a[i]);
  ll sum=0;
  for(int i=1;i<=n;i++)
    {
      ll got=get(a[i]-1);
      update(a[i],got+w[a[i]]); sum+=w[i];
    }
  printf("%lld\n",(sum-get((1<<17))));
}
