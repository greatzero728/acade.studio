#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<queue>
#include<map>
using namespace std;
typedef long long LL;
const int N=6e5+100;
int gi() {
	int w=0;bool q=1;char c=getchar();
	while ((c<'0'||c>'9') && c!='-') c=getchar();
	if (c=='-') q=0,c=getchar();
	while (c>='0'&&c <= '9') w=w*10+c-'0',c=getchar();
	return q? w:-w;
}
int c[N],sa[N],rk[N],lim[N];
pair<int,int>eve[N];

int one[N],other[N];
map<int,int>two[N];
int st[N],in[N],pos[N];

pair<int,int>ask[N];
int ans[N];

inline bool cmp(const int &a,const int &b) { return c[a]<c[b]; }

#define lc (i<<1)
#define rc (lc|1)
int mx[N<<2];
inline void modify(int i,int l,int r,int k,int t) {
	if (l==r) mx[i]=t;
	else {
		int mid=(l+r)>>1;
		k<=mid?modify(lc,l,mid,k,t):modify(rc,mid+1,r,k,t);
		mx[i]=max(mx[lc],mx[rc]);
	}
}
inline int query(int i,int l,int r,int L,int R) {
	if (L<=l&&r<=R) return mx[i];
	else {
		int mid=(l+r)>>1;
		if (R<=mid) return query(lc,l,mid,L,R);
		if (mid<L) return query(rc,mid+1,r,L,R);
		return max(query(lc,l,mid,L,R),query(rc,mid+1,r,L,R));
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("E.in","r",stdin);
	freopen("E.out","w",stdout);
#endif
	int n=gi(),m,C=gi(),i,k,t,l,r,len=0,cur;
	for (i=1;i<=n;i++) {
		l=gi(),r=gi(),c[i]=gi();
		eve[++len]=make_pair(l,i);
		eve[++len]=make_pair(r,-i);
	}
	
	for (i=1;i<=n;i++) sa[i]=i;
	sort(sa+1,sa+1+n,cmp);
	for (i=1,k=n;i<=n;i++) {
		rk[sa[i]]=i;
		while (k&&c[sa[i]]+c[sa[k]]>C) k--;
		lim[i]=k;
	}

	for (i=1,m=gi();i<=m;i++) ask[i]=make_pair(gi(),i);
	sort(ask+1,ask+1+m);
	
	int free=0,top=0,now,use=0;
	eve[++len].first=(1LL<<31)-1;
	sort(eve+1,eve+1+len);

	for (i=cur=1;cur<=m;i++) {
		
		now=eve[i].first-eve[i-1].first;
		
		if (top==2&&c[k=st[1]]+c[t=st[2]]<=C) {
			two[k][t]+=now;
			two[t][k]+=now;
			other[k]=max(other[k],two[k][t]+one[t]);
			other[t]=max(other[t],two[k][t]+one[k]);
			use=max(use,one[k]+one[t]+two[k][t]);
		} else if (top==1&&c[k=st[1]]<=C) {
			modify(1,1,n,rk[k],one[k]+=now);
			use=max(use,one[k]+other[k]);
			if (rk[k]!=1&&lim[rk[k]])
				use=max(use,one[k]+query(1,1,n,1,min(rk[k]-1,lim[rk[k]])));
			if (rk[k]!=n&&lim[rk[k]]>rk[k])
				use=max(use,one[k]+query(1,1,n,rk[k]+1,lim[rk[k]]));
		} else if (!top) free+=now;

		if ((k=eve[i].second)>0)
			st[pos[k]=++top]=k;
		else
			t=pos[-k],pos[st[t]=st[top--]]=t;

		while (cur<=m&&ask[cur].first<=free+use)
			ans[ask[cur].second]=eve[i].first-(free+use-ask[cur].first),cur++;
	}
	for (i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
