#include<bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
const int N=2e6+5;
int n,m,a[N],b[N],c[N],p[N],min1[N],min2[N],lsh[N],bit[N],cnt;
ll res;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		c=getchar();
		continue;
	}
	while(c>='0'&&c<='9') {
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x;
}
int getx(int x) {
	return lower_bound(lsh+1,lsh+1+cnt,x)-lsh;
}
void upd(int x,int k) {
	for(int i=x;i<=cnt;i+=i&-i) bit[i]+=k;
}
int qry(int x) {
	int tot=0;
	for(int i=x;i;i-=i&-i) tot+=bit[i];
	return tot;
}
void solve() {
//	for(int i=1;i<=m;i++) {
//		printf("%d\n",p[i]);
//	}
	cnt=0;
	int i=1,j=1;
	while(i<=n&&j<=m) {
		if(i<p[j]) {
			c[++cnt]=a[i++];
		}
		else {
			c[++cnt]=b[j++];
		}
	}
	while(i<=n) {
		c[++cnt]=a[i++];
	}
	while(j<=m) {
		c[++cnt]=b[j++];
	}
	for(int i=1;i<=cnt;i++) lsh[i]=c[i];
	sort(lsh+1,lsh+1+cnt),cnt=unique(lsh+1,lsh+1+cnt)-lsh-1;
	for(int i=n+m;i>=1;i--) {
		c[i]=getx(c[i]);
		res+=qry(c[i]-1);
		upd(c[i],1);
	}
	for(int i=1;i<=n+m;i++) {
		upd(c[i],-1);
	}
}
//p1 <= p2 <= ... <= pn
void divide(int l,int r,int ql,int qr) {
	if(l>r) {
		return;
	}
	int mid=l+r>>1,pos=0,tmp=inf;
	min1[ql]=min2[qr]=0;
	for(int i=ql+1;i<=qr;i++) {
		min1[i]=min1[i-1]+(a[i-1]>b[mid]);
	}
	for(int i=qr-1;i>=ql;i--) {
		min2[i]=min2[i+1]+(a[i]<b[mid]);
	}
	for(int i=ql;i<=qr;i++) {
		if(min1[i]+min2[i]<tmp) {
			tmp=min1[i]+min2[i];
			pos=i;
		}
	}
	p[mid]=pos;
	divide(l,mid-1,ql,pos);
	divide(mid+1,r,pos,qr);
}
//????
//shit 
int main() {
	int T=read();
	while(T--) {
		n=read(),m=read(); res=0;
		for(int i=1;i<=n;i++) a[i]=read();
		for(int i=1;i<=m;i++) b[i]=read();
		sort(b+1,b+1+m);
		divide(1,m,1,n+1);
		solve();
		printf("%lld\n",res);
	}
}