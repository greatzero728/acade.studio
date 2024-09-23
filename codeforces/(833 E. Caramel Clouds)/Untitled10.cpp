// LUOGU_RID: 137193361
#include<stdio.h>
#include<algorithm>
#include<map>
#include<set>
#define N 300009
#define pr pair<int,int> 
#define lc ((i)<<1|1)
#define rc ((i)+1<<1)
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,m,p,q,c[N],lsh[N],ans[N],fre,maxn,id[N],tre[N<<2],max2[N];
struct node
{
	int x,i;
	inline bool operator<(node kkk)const{return x<kkk.x;}
}a[N<<1],b[N];
set<int>s;map<int,int>len;map<pr,int>len2;
inline void upd(int i,int l,int r,int p,int x)
{
	tre[i]=max(tre[i],x);
	if(l==r)return;
	int mid=l+r>>1;
	if(p<=mid)upd(lc,l,mid,p,x);
	else upd(rc,mid+1,r,p,x);
}
inline int qry(int i,int l,int r,int ql,int qr)
{
	if(qr<l||r<ql)return 0;
	if(ql<=l&&r<=qr)return tre[i];
	int mid=l+r>>1;
	return max(qry(lc,l,mid,ql,qr),qry(rc,mid+1,r,ql,qr));
}
main()
{
	read(n);read(m);
	for(int i=0;i<n;++i)
	{
		read(a[i].x);a[i].i=i;
		read(a[i+n].x);a[i+n].i=~i;
		read(c[i]);lsh[i]=c[i];
	}
	read(q);
	for(int i=0;i<q;++i)read(b[i].x),b[i].i=i;
	sort(a,a+(n<<1));sort(b,b+q);a[n<<1].x=2000000000;
	sort(lsh,lsh+n);
	for(int i=0;i<n;++i)
		id[i]=lower_bound(lsh,lsh+n,c[i])-lsh,--lsh[id[i]];
	for(int i=0;i<n;++lsh[i++]);
	for(int i=0,lst=0,j=0;j<q;++i)
	{
		if(a[i].x^lst)switch(s.size())
		{
			case 0:fre+=a[i].x-lst;break;
			case 1:if(c[*s.begin()]>m)break;
				len[*s.begin()]+=a[i].x-lst;
				maxn=max(maxn,max2[*s.begin()]+=a[i].x-lst);
				upd(0,0,n-1,id[*s.begin()],len[*s.begin()]);
				p=upper_bound(lsh,lsh+n,m-c[*s.begin()])-lsh-1;
				if(p<id[*s.begin()])maxn=max(maxn,
					len[*s.begin()]+qry(0,0,n-1,0,p));
				else maxn=max(maxn,len[*s.begin()]+
					max(qry(0,0,n-1,0,id[*s.begin()]-1),
						qry(0,0,n-1,id[*s.begin()]+1,p)));
				break;
			case 2:if(c[*s.begin()]+c[*s.rbegin()]>m)break;
				len2[(pr){*s.begin(),*s.rbegin()}]+=a[i].x-lst;
				max2[*s.begin()]=max(max2[*s.begin()],
					len[*s.begin()]+len[*s.rbegin()]+
					len2[(pr){*s.begin(),*s.rbegin()}]);
				max2[*s.rbegin()]=max(max2[*s.rbegin()],
					len[*s.begin()]+len[*s.rbegin()]+
					len2[(pr){*s.begin(),*s.rbegin()}]);
				maxn=max(maxn,max2[*s.begin()]);
		}
		for(;j<q&&fre+maxn>=b[j].x;++j)
			ans[b[j].i]=a[i].x-(fre+maxn-b[j].x);
		if(j==q)break;
		lst=a[i].x;
		if(a[i].i>>31)s.erase(~a[i].i);
		else s.emplace(a[i].i);
	}
	for(int i=0;i<q;printf("%d\n",ans[i++]));
}