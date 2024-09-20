#include<bits/stdc++.h>
#define re register
#define inc(i,j,k) for(re int i=j;i<=k;i++)
#define dec(i,j,k) for(re int i=j;i>=k;i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
using namespace std; 
const int N=505;
const int M=6e5+5;
inline int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while('0'<=ch&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}
bitset<N*N> b[N];
int n,m,q; 
char s[N][N];
vector<pair<int,int> >v[N][N];
bool ans[M];
int id(int i,int j){return m*(i-1)+j;}
int main(){
	n=read(),m=read();
	inc(i,1,n) scanf("%s",s[i]+1);
	q=read();
	inc(i,1,q){
		int x_1=read(),y_1=read(),x_2=read(),y_2=read();
		v[x_1][y_1].pb(mp(id(x_2,y_2),i));
	}
	int t=0;
	dec(i,n,1){
		dec(j,m,1){
			b[j]|=b[j+1],b[j][id(i,j)]=1;
			if(s[i][j]=='#') b[j].reset();
			for(re int k=0;k<v[i][j].size();k++){
				ans[v[i][j][k].se]=b[j][v[i][j][k].fi];
			}
		}
	}
	inc(i,1,q){
		if(ans[i]) puts("Yes");
		else puts("No");
	}
}