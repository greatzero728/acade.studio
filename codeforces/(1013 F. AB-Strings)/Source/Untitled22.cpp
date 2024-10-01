#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define uint ungigned
#define db long double
#define pii pair<int,int>
#define IT iterator

#define PB push_back
#define MK make_pair
#define LB lower_bound
#define UB upper_bound
#define fi first
#define se second

#define For(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define Rep(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define UPD(x,y) (((x)+=(y))>=mo?x-=mo:233)
#define CLR(a,v) memset(a,v,sizeof(a));
#define CPY(a,b) memcpy(a,b,sizeof(a));

#define LS3 k*2,l,mid
#define RS3 k*2+1,mid+1,r
#define LS5 k*2,l,mid,x,y
#define RS5 k*2+1,mid+1,r,x,y
#define GET pushdown(k);int mid=(l+r)/2

#define INF ((1<<30)-233)
#define sqr(x) ((x)*(x))
#define debug puts("wzpkking")
using namespace std;

const int N=400005;
int calc(int n,int m,int x,int y){
	if (n&&m&&x==y)
		n<m?n++:m++;
	return max(n,m)-1;
}

char s[N],t[N];
vector<int> S,T;
int main(){
	scanf("%s%s",s,t);
	int ls=strlen(s),n=0;
	int lt=strlen(t),m=0;
	For(i,0,ls-1) n+=(i==0||s[i]!=s[i-1]);
	For(i,0,lt-1) m+=(i==0||t[i]!=t[i-1]);
	int ans=calc(n,m,s[0]=='a',t[0]=='a');
	int xx=0,yy=0,n2=0,m2=0;
	For(i,0,ls) if (i==0||i==ls||s[i]!=s[i-1]){
		m2=0;
		For(j,0,lt) if (j==0||j==lt||t[j]!=t[j-1]){
			int n3=n-n2+m2-(i<ls&&j&&t[j-1]==s[i]);
			int m3=m-m2+n2-(j<lt&&i&&s[i-1]==t[j]);
			int x3=(j?t[0]=='a':(i<ls?s[i]=='a':0));
			int y3=(i?s[0]=='a':(j<lt?t[j]=='a':0));
			int tmp=1+calc(n3,m3,x3,y3);
			if (tmp<ans) ans=tmp,xx=i,yy=j;
			m2++;
		}
		if ((++n2)>3) break;
	}
	n2=m2=0;
	For(j,0,lt) if (j==0||j==lt||t[j]!=t[j-1]){
		n2=0;
		For(i,0,ls) if (i==0||i==ls||s[i]!=s[i-1]){
			int n3=n-n2+m2-(i<ls&&j&&t[j-1]==s[i]);
			int m3=m-m2+n2-(j<lt&&i&&s[i-1]==t[j]);
			int x3=(j?t[0]=='a':(i<ls?s[i]=='a':0));
			int y3=(i?s[0]=='a':(j<lt?t[j]=='a':0));
			int tmp=1+calc(n3,m3,x3,y3);
			if (tmp<ans) ans=tmp,xx=i,yy=j;
			n2++;
		}
		if ((++m2)>3) break;
	}
	int d=0;
	printf("%d\n",ans);
	if (xx||yy){
		static char ss[N],tt[N];
		For(i,0,ls-1) ss[i]=s[i];
		For(i,0,lt-1) tt[i]=t[i];
		int lS=ls,lT=lt; ls=lt=0;
		For(i,0,yy-1) s[ls++]=tt[i];
		For(i,xx,lS-1) s[ls++]=ss[i];
		For(i,0,xx-1) t[lt++]=ss[i]; 
		For(i,yy,lT-1) t[lt++]=tt[i];
		printf("%d %d\n",xx,yy);
	}
	For(i,1,ls-1) if (s[i]!=s[i-1]) S.PB(i);
	For(i,1,lt-1) if (t[i]!=t[i-1]) T.PB(i);
	if (ls&&lt&&s[0]==t[0])
		S.size()<T.size()?S.PB(0):T.PB(0);
	sort(S.begin(),S.end());
	sort(T.begin(),T.end());
	int i=0,j=0;
	for (;i<S.size()||j<T.size();){
		int x=(i==S.size()?ls:S[i]);
		int y=(j==T.size()?lt:T[j]);
		printf("%d %d\n",x+d,y-d);
		d+=(y-d)-(x+d);
		if (i<S.size()) i++;
		if (j<T.size()) j++;
	} 
	
} 
