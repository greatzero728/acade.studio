// LUOGU_RID: 113323004
#include<bits/stdc++.h>
#define inf 0x7f7f7f7f
using namespace std;
const int MxN=300002;
int n,C,m,t=0,t1=0,h=0,L,R,mid;
int l[MxN],r[MxN],c[MxN],val[MxN<<1],id[MxN<<1],val2[MxN<<1],f[MxN<<1],cnt[MxN<<1],to[MxN],cnt1[MxN<<1];
vector<int> vec[MxN<<1],vec2[MxN<<1];
set<int> s;
set<int>::iterator it;
inline int lson(int x)
{
	return (x<<1);
}
inline int rson(int x)
{
	return (x<<1)|1;
}
struct SegTree
{
	int mx[MxN<<2];
	inline void modify(int k,int l,int r,int x,int d)
	{
		if(l==r)return (void)(mx[k]+=d);
		int mid=((l+r)>>1),ls=lson(k),rs=rson(k);
		if(x<=mid)modify(ls,l,mid,x,d);
		else modify(rs,mid+1,r,x,d);
		mx[k]=max(mx[ls],mx[rs]);
	}
	inline int query(int k,int l,int r,int x)
	{
		if(r<=x)return mx[k];
		int mid=((l+r)>>1),ls=lson(k),rs=rson(k);
		if(x<=mid)return query(ls,l,mid,x);
		return max(mx[ls],query(rs,mid+1,r,x));
	}
}S;
inline bool cmp(int x,int y)
{
	return val[x]<val[y];
}
inline bool cmp2(int x,int y)
{
	return c[x]<c[y];
}
int main()
{
	scanf("%d%d",&n,&C);
	for(int i=1;i<=n;++i)scanf("%d%d%d",&l[i],&r[i],&c[i]),val[++t]=l[i],val[++t]=r[i];
	for(int i=1;i<=t;++i)id[i]=i;
	sort(id+1,id+t+1,cmp);
	for(int i=1;i<=t;++i)t1+=(i==1 || val[id[i]]!=val[id[i-1]]),(id[i]&1? l[(id[i]+1)>>1]:r[id[i]>>1])=t1,val2[t1]=val[id[i]];
	val2[++t1]=inf;
	for(int i=1;i<=t1;++i)s.insert(i);
	for(int i=1;i<=n;++i)vec2[r[i]].push_back(i);
	for(int i=1;i<=t1;++i)for(int j=0;j<vec2[i].size();++j)for(it=s.lower_bound(l[vec2[i][j]]+1);it!=s.end() && *it<=i;)
	{
		++cnt[*it];
		if(cnt[*it]<=2)vec[*it].push_back(vec2[i][j]),++it;else it=s.erase(it);
	}
	for(int i=1;i<=t1;++i)s.insert(i);
	for(int i=1;i<=n;++i)id[i]=i;
	sort(id+1,id+n+1,cmp2);
	for(int i=1;i<=n;++i)to[id[i]]=i;
	for(int i=1;i<=t1;++i)
	{
		if(!cnt[i])
		{
			f[i]=f[i-1]+val2[i]-val2[i-1];
			goto f1;
		}
		f[i]=f[i-1];
		if(cnt[i]>2)goto f1;
		if(cnt[i]==2)
		{
			if(c[vec[i][0]]+c[vec[i][1]]<=C)f[i]=max(f[i],val2[i]-val2[i-1]+h);
			goto f1;
		}
		if(c[vec[i][0]]<=C)
		{
			for(L=1,R=n;L<=R;)
			{
				mid=((L+R)>>1);
				if(c[vec[i][0]]+c[id[mid]]<=C)L=mid+1;
				else R=mid-1;
			}
			f[i]=max(f[i],val2[i]-val2[i-1]+h+(R? S.query(1,1,n,R):0));
		}
		f1:
		h+=val2[i]-val2[i-1];
		for(int j=0,g;j<vec2[i].size();++j)
		{
			for(g=0,it=s.lower_bound(l[vec2[i][j]]+1);it!=s.end() && *it<=i;)
			{
				if(!cnt1[*it])g+=val2[*it]-val2[*it-1],h-=val2[*it]-val2[*it-1];
				else if(cnt1[*it]==1)S.modify(1,1,n,to[vec[*it][0]],val2[*it-1]-val2[*it]);
				++cnt1[*it];
				if(cnt1[*it]<=2)++it;else it=s.erase(it);
			}
			S.modify(1,1,n,to[vec2[i][j]],g);
		}
	}
	scanf("%d",&m);
	for(int k;m--;)
	{
		for(scanf("%d",&k),L=0,R=t1;L<=R;)
		{
			mid=((L+R)>>1);
			if(f[mid]>=k)R=mid-1;
			else L=mid+1;
		}
		printf("%d\n",val2[L]-f[L]+k);
	}
	return 0;
}