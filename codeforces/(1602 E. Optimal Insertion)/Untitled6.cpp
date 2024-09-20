#include<bits/stdc++.h>
#define mid ((l+r)>>1)
using namespace std;
const int N=1000005;
int t,n,m;
int a[N],b[N],tmp[N*2];
int tr[N*4],add[N*4],pre[N],suf[N];
void build(int rt,int l,int r)
{
	add[rt]=0;
	if(l==r)return tr[rt]=suf[l+1]+pre[l],void();
	build(rt<<1,l,mid);build(rt<<1|1,mid+1,r);
	tr[rt]=min(tr[rt<<1],tr[rt<<1|1]);
}
void pushdown(int rt,int l,int r)
{
	if(!add[rt])return;
	tr[rt<<1]+=add[rt];
	tr[rt<<1|1]+=add[rt];
	add[rt<<1]+=add[rt];
	add[rt<<1|1]+=add[rt];
	add[rt]=0;
}
void update(int rt,int l,int r,int L,int R,int k)
{
	if(r<L||R<l)return;
	if(L<=l&&r<=R){tr[rt]+=k;add[rt]+=k;return;}
	pushdown(rt,l,r);
	update(rt<<1,l,mid,L,R,k);
	update(rt<<1|1,mid+1,r,L,R,k);
	tr[rt]=min(tr[rt<<1],tr[rt<<1|1]);
}
int s[N*2],tot[N*2];vector<int> pos[N*2];
int lowbit(int x){return x&(-x);}
void Add(int x,int k){for(;x<N*2;x+=lowbit(x))s[x]+=k;}
int sum(int x){int ret=0;for(;x;x-=lowbit(x))ret+=s[x];return ret;}
int main()
{
	scanf("%d",&t);	
	while(t--)
	{
		scanf("%d%d",&n,&m);int cnt=0;
		for(int i=1;i<=n;++i)scanf("%d",&a[i]),tmp[++cnt]=a[i];
		for(int i=1;i<=m;++i)scanf("%d",&b[i]),tmp[++cnt]=b[i];
		sort(tmp+1,tmp+cnt+1);int len=unique(tmp+1,tmp+cnt+1)-tmp-1;for(int i=1;i<=cnt;++i)pos[i].clear(),tot[i]=0;
		for(int i=1;i<=n;++i)a[i]=lower_bound(tmp+1,tmp+len+1,a[i])-tmp,pos[a[i]].push_back(i),tot[a[i]]++;
		for(int i=1;i<=m;++i)b[i]=lower_bound(tmp+1,tmp+len+1,b[i])-tmp;sort(b+1,b+m+1);
		for(int i=1;i<=n;++i)pre[i]=pre[i-1]+(a[i]>b[1]);
		suf[n+1]=0;for(int i=n;i;--i)suf[i]=suf[i+1]+(a[i]<b[1]);
		build(1,1,n);long long ans=0;
		for(int i=n;i;--i){Add(a[i],1);ans+=sum(a[i]-1);}
		for(int i=n;i;--i)Add(a[i],-1);
		for(int i=1;i<=cnt;++i)tot[i]+=tot[i-1];
		for(int i=1;i<=m;++i)
		{
			ans+=min(tr[1],tot[b[i]-1]);if(i==m||b[i]==b[i+1])continue;
			for(int j=b[i]+1;j<=b[i+1]-1;++j)
			for(int p:pos[j])update(1,1,n,1,p-1,1),update(1,1,n,p,n,-1);
			for(int p:pos[b[i]])update(1,1,n,1,p-1,1);
			for(int p:pos[b[i+1]])update(1,1,n,p,n,-1);
		}
		printf("%lld\n",ans);
	}
	return 0;
}