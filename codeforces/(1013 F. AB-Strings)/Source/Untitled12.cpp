#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
string a,b;int ans=1e9;bool flg;
pii A[200004],B[200004];int NA,NB;
pii C[400004],D[400004];int NC,ND;
int X,Y,Z,f[400004],g[400004];vector<pii>arr;
void calc(){
	NC=ND=0;int P=0,Q=0;
	for(int i=1;i<=Y;i++)C[++NC]=B[i],Q+=B[i].se;
	for(int i=1;i<=X;i++)D[++ND]=A[i],P+=A[i].se;
	for(int i=X+1;i<=NA;i++){
		if(NC&&C[NC].fi==A[i].fi)C[NC].se+=A[i].se;
		else C[++NC]=A[i];
	}
	for(int i=Y+1;i<=NB;i++){
		if(ND&&D[ND].fi==B[i].fi)D[ND].se+=B[i].se;
		else D[++ND]=B[i];
	}
	if(P||Q)arr.push_back({P,Q});
	if(NC&&Z==C[NC].fi)NC--;
	if(ND&&1-Z==D[ND].fi)ND--;
	for(int i=1;i<=NC;i++)f[i]=f[i-1]+C[i].se;
	for(int i=1;i<=ND;i++)g[i]=g[i-1]+D[i].se;
	for(int i=NC,j=ND,k=1;i>0||j>0;i--,j--,k^=1){
		P=i<1?0:f[i],Q=j<1?0:g[j];
		if(k)arr.push_back({P,Q});
		else arr.push_back({Q,P});
	}
}
int main(){
//	freopen("in.txt","r",stdin);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0),cin>>a>>b;
	for(int i=0,j;i<a.size();i=j){
		for(j=i+1;j<a.size()&&a[i]==a[j];j++);
		A[++NA]={a[i]-'a',j-i};
	}
	for(int i=0,j;i<b.size();i=j){
		for(j=i+1;j<b.size()&&b[i]==b[j];j++);
		B[++NB]={b[i]-'a',j-i};
	}
	if(NA>NB){
		swap(NA,NB),flg=1;
		for(int i=1;i<=max(NA,NB);i++)swap(A[i],B[i]);
	}
	int t=(NB-NA)/2-4,ans=1e9;if(t<0)t=0;
	for(int x=0;x<=8&&x<=NA;x++)
		for(int y=t;y<=t+8&&y<=NB;y++){
			NC=ND=0;
			for(int i=1;i<=y;i++)C[++NC]=B[i];
			for(int i=1;i<=x;i++)D[++ND]=A[i];
			for(int i=x+1;i<=NA;i++){
				if(NC&&C[NC].fi==A[i].fi)C[NC].se+=A[i].se;
				else C[++NC]=A[i];
			}
			for(int i=y+1;i<=NB;i++){
				if(ND&&D[ND].fi==B[i].fi)D[ND].se+=B[i].se;
				else D[++ND]=B[i];
			}
			for(int z=0;z<2;z++){
				int VC=NC,VD=ND;
				if(NC&&z==C[NC].fi)VC--;
				if(ND&&1-z==D[ND].fi)VD--;
				int res=max(VC,VD)+(x>0||y>0);
				if(res<ans)ans=res,X=x,Y=y,Z=z;
			}
		}
	calc(),cout<<ans<<"\n";
	for(auto[x,y]:arr){
		if(flg)cout<<y<<" "<<x<<"\n";
		else cout<<x<<" "<<y<<"\n";
	}
}