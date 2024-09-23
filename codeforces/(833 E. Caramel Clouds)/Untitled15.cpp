#include<bits/stdc++.h>
using namespace std;
const int N=6e5+5,inf=2e9;
int n,c,b[N],cntb,maxn[N],cnt[N],mx2[N],m;
struct abc{int l,r,c;}a[N];
bool cmp(abc a,abc b){if(a.c!=b.c)return a.c<b.c;if(a.l!=b.l)return a.l<b.l;return a.r<b.r;}
vector<int>in[N],out[N];
int lowbit(int x){return (x&-x);}
struct BIT
{
	int t[2][N];
	void change(int x,int v)
	{
		for(int i=x;i<N;i+=lowbit(i))
		{
			if(cnt[v]>cnt[t[0][i]])t[1][i]=t[0][i],t[0][i]=v;
			else if(v!=t[0][i] && cnt[v]>cnt[t[1][i]])t[1][i]=v;
		}
	}
	int ask(int x,int v)
	{
		int ans=0;
		for(int i=x;i>=1;i-=lowbit(i))
		{
			if(t[0][i]!=v && cnt[t[0][i]]>ans)ans=cnt[t[0][i]];
			if(cnt[t[1][i]]>ans)ans=cnt[t[1][i]];
		}
		return ans;
	}
}t;
map<int,int>mp[N];
int main()
{
	scanf("%d %d",&n,&c);
	for(int i=1;i<=n;i++)scanf("%d %d %d",&a[i].l,&a[i].r,&a[i].c),b[++cntb]=a[i].l,b[++cntb]=a[i].r;
	sort(b+1,b+cntb+1),cntb=unique(b+1,b+cntb+1)-b-1;
	for(int i=1;i<=n;i++)a[i].l=lower_bound(b+1,b+cntb+1,a[i].l)-b,a[i].r=lower_bound(b+1,b+cntb+1,a[i].r)-b;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)in[a[i].l+1].push_back(i),out[a[i].r+1].push_back(i);
//	for(int i=1;i<=n;i++)printf("%d %d %d\n",a[i].l,a[i].r,a[i].c);
	set<int>s;
	int max1=0,max2=0,rres=0;
	for(int i=1;i<=cntb;i++)
	{
		for(auto j:in[i])s.insert(j);
		for(auto j:out[i])s.erase(j);
//		cout<<i<<" "<<s.size()<<endl;
//		if(s.size()>=2)cout<<(*s.begin())<<" "<<(*s.rbegin())<<endl;
		if(s.size()>=3){maxn[i]=max(max1,max2)+rres;continue;}
		if(s.size()==0)rres+=b[i]-b[i-1],maxn[i]=max(max1,max2)+rres;
		else if(s.size()==2)
		{
			int x=(*s.begin()),y=(*s.rbegin());
//			cout<<x<<" "<<y<<" "<<a[x].c+a[y].c<<endl;
			if(a[x].c+a[y].c<=c)
			{
//				cout<<i<<" "<<x<<" "<<y<<endl;
				mp[x][y]+=b[i]-b[i-1],mp[y][x]+=b[i]-b[i-1],mx2[x]=max(mx2[x],cnt[x]+mp[x][y]+cnt[y]),mx2[y]=max(mx2[y],cnt[y]+mp[x][y]+cnt[x]);
				max2=max(max2,mx2[x]),max2=max(max2,mx2[y]);
			}
			maxn[i]=max(max1,max2)+rres;
		}
		else if(s.size()==1)
		{
			int x=(*s.begin());
			mx2[x]+=b[i]-b[i-1],cnt[x]+=b[i]-b[i-1],t.change(x,x);
			int pos=lower_bound(a+1,a+n+1,(abc){inf,inf,c-a[x].c},cmp)-a-1;
//			cout<<i<<" "<<pos<<" "<<a[x].c<<endl;
			if(a[x].c<=c)
			{
				max2=max(max2,mx2[x]);
				max1=max(max1,t.ask(pos,x)+cnt[x]);
			}
//			cout<<max1<<" ss "<<max2<<endl;
			maxn[i]=max(max1,max2)+rres;
		}
	}
//	for(int i=1;i<=cntb;i++)printf("%d ",maxn[i]);printf("\n");
	scanf("%d",&m);
	while(m--)
	{
		int x;
		scanf("%d",&x);
		int pos=lower_bound(maxn+1,maxn+cntb+1,x)-maxn;
		if(pos==cntb+1)printf("%d\n",b[cntb]+x-maxn[cntb]);
		else printf("%d\n",b[pos]-maxn[pos]+x);
	}
	return 0;
}