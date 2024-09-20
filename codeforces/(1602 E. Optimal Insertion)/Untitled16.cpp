#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
using ll=long long;
using ull=unsigned long long;
using lll=__int128;
using db=double;
using ld=long double;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using vi=vector<int>;
using vl=vector<ll>;
using vii=vector<pii>;
using vll=vector<pll>;
mt19937 rnd(random_device{}());
mt19937_64 rnd64(random_device{}());
const int N=1e6+5;
int n,m;
int a[N],b[N];
int va[N],pu;
int fw[N];
ll ans;
void add(int x,int d)
{
	for (;x<=n;x+=x&-x) fw[x]+=d;
}
int query(int x)
{
	int res=0;
	for (;x;x-=x&-x) res+=fw[x];
	return res;
}
void task()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=m;i++) scanf("%d",&b[i]);
	ans=0;
	for (int i=1;i<=n;i++) va[i]=a[i];
	sort(va+1,va+n+1);
	for (int i=1;i<=n;i++) fw[i]=0;
	for (int i=n;i>=1;i--)
	{
		int v=lower_bound(va+1,va+n+1,a[i])-va;
		ans+=query(v-1);
		add(v,1);
	}
	// printf("ans=%lld\n",ans);
	sort(b+1,b+m+1);
	priority_queue<int> q;
	for (int i=1;i<=n;i++)
	{
		int x=lower_bound(b+1,b+m+1,a[i])-b;
		int y=upper_bound(b+1,b+m+1,a[i])-b;
		// printf("[%d %d]\n",x,y);
		if (!q.empty()&&q.top()>y) 
		{
			ans+=q.top()-y;
			q.pop();
			q.emplace(y);
		}
		q.emplace(x);
	}
	printf("%lld\n",ans);
}
int main()
{
	int T;
	scanf("%d",&T);
	while (T--) task();
}
/*
6 4 2
1 3 6 4 5 
 */