#include<bits/stdc++.h>
#define int long long
#define gmax(x,y) x=max(x,y)
#define gmin(x,y) x=min(x,y)
#define F first
#define S second
#define P pair
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define rep(i,a,b) for(int i=a;i<b;i++)
#define V vector
#define RE return
#define ALL(a) a.begin(),a.end()
#define MP make_pair
#define PB emplace_back
#define PF push_front
#define FILL(a,b) memset(a,b,sizeof(a))
#define lwb lower_bound
#define upb upper_bound
#define lc (x<<1)
#define rc ((x<<1)|1)
#define sz(x) ((int)x.size())
#define pc putchar
using namespace std;
int X[2][4]={
0,0,0,1,1,1,1,1
},Y[2][4]={2,1,0,1,2,1,2,3};
int n,m;
string s,t;
V<P<int,int> > ans;
int pos1[200005],pos2[200005];
bool f=0;
void solve(){
	n=m=0;
	rep(i,0,sz(s)-1)if(s[i]!=s[i+1])pos1[++n]=i+1;
	pos1[++n]=sz(s);
	rep(i,0,sz(t)-1)if(t[i]!=t[i+1])pos2[++m]=i+1;
	pos2[++m]=sz(t);
	if(n>m){
		FOR(i,1,max(n,m))swap(pos1[i],pos2[i]);
		swap(n,m);
		swap(s,t);
		f^=1;
	}
}
void SWAP(int x,int y){
	if(f)ans.PB(MP(y,x));else ans.PB(MP(x,y));
	string p1=s.substr(0,x),p2=t.substr(0,y);
	s=p2+s.substr(x),t=p1+t.substr(y);
	solve();
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>s>>t;
	solve();
	if(m>n+1){
		int t1=s[0]!=t[0],t2=(m-n)&3;
		SWAP(pos1[X[t1][t2]],pos2[(m-n+Y[t1][t2])/2]);
	}
	if(s[0]==t[0])SWAP(0,pos2[1]);
	while(n!=m)SWAP(pos1[n],pos2[n]);
	for(int i=n-1;i>=1;i--){
		if(!f)ans.PB(pos1[i],pos2[i]);
		else ans.PB(MP(pos2[i],pos1[i]));
		f^=1;
	}
	cout<<sz(ans)<<'\n';
	for(auto u:ans)cout<<u.F<<' '<<u.S<<'\n';
	RE 0;
}



