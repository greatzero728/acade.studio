#include<bits/stdc++.h>
#define For(i,x,y) for (int i=(x);i<=(y);i++)
#define FOR(i,x,y) for (int i=(x);i<(y);i++)
#define Dow(i,x,y) for (int i=(x);i>=(y);i--)
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define ep emplace_back
#define siz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define fil(a,b) memset((a),(b),sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pa;
typedef pair<ll,ll> PA;
typedef vector<int> poly;
inline ll read(){
	ll x=0,f=1;char c=getchar();
	while ((c<'0'||c>'9')&&(c!='-')) c=getchar();
	if (c=='-') f=-1,c=getchar();
	while (c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x*f;
}

const int N = 5e5+10;
int n,m;
char s[N],t[N];
bool flag;

vector<pa>a,b,ans;
inline void ins(vector<pa>&v,pa x){
	if (v.empty()||v.back().fi!=x.fi) v.pb(x);
		else v.back().se+=x.se;
}
inline void Swap(int x){
	int len=0;
	pa tmp=a.back();a.pop_back();
	Dow(i,x,1){
		ins(a,b[siz(b)-i]);
		len+=b[siz(b)-i].se;
	}
	ans.ep(tmp.se,len);
	For(i,1,x) b.pop_back();
	ins(b,tmp);
}

int main(){
	scanf("%s%s",s+1,t+1),n=strlen(s+1),m=strlen(t+1);
	Dow(i,n,1) ins(a,mp(s[i]-'a',1));
	Dow(i,m,1) ins(b,mp(t[i]-'a',1));
	if (siz(a)>siz(b)) swap(a,b),flag=1;
	if (s[1]==t[1]){
		if ((siz(b)-siz(a))%4==3) Swap((siz(b)-siz(a)+1)/2);
		int tmp=(siz(b)-siz(a))/4*2+1;
		a.ep(b[siz(b)-tmp-1].fi,0);
		Swap(tmp);		
	} else if (siz(b)-siz(a)>2) Swap((siz(b)-siz(a)+1)/4*2+1);
	while (siz(a)>1||siz(b)>1) Swap(1);
	printf("%d\n",siz(ans));
	for (auto [i,j]:ans){
		if (flag) swap(i,j);
		printf("%d %d\n",i,j);
	}
}