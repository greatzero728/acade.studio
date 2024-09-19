#include<bits/stdc++.h>
using namespace std;
using ull=uint64_t;
#define rep(i,a,b) for(int i=a,i##end=b;i<=i##end;++i)
enum{N=2000,K=2001};
int n,m,A[N][N],B[N][N],I[N],J[N];
ull HA[N],HB[N];
int F[N][N],D[N],del[N],Q[N],L,R;
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n) rep(j,1,m) scanf("%d",A[i]+j),HA[i]=HA[i]*K+A[i][j];
	rep(i,1,n) rep(j,1,m) scanf("%d",B[i]+j),HB[i]=HB[i]*K+B[i][j];
	rep(i,1,n) rep(j,1,n) if(!J[j] && HB[i]==HA[j]) { I[i]=j,J[j]=i; break; }
	rep(i,1,n) if(!I[i]) return puts("-1"),0;
	rep(i,1,m) {
		rep(j,1,n-1) {
			int x=A[I[j]][i],y=A[I[j+1]][i];
			F[i][j]=x<y?2:x==y;
			if(!F[i][j]) D[i]++;
		}
		if(!D[i]) Q[++R]=i;
	}
	while(L<=R) {
		int u=Q[L++];
		rep(i,1,n-1) if(F[u][i]==2 && !del[i]) {
			del[i]=1;
			rep(j,1,m) if(!F[j][i] && --D[j]==0) Q[++R]=j;
		}
	}
	rep(i,1,n-1) if(!del[i] && I[i]>I[i+1]) return puts("-1"),0;
	printf("%d\n",R);
	while(R) printf("%d ",Q[R--]);
}
		 			  		  						   	  			 		