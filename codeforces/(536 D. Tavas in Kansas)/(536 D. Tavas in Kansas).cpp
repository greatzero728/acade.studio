#include<bits/stdc++.h>
#define N 2005
#define INF 0x3f3f3f3f3f3f3f3fll
using namespace std;
typedef long long ll;
int n,m,s,t,s2[N][N],a[N],t1,t2,l[N][N],r[N][N],used[N],g[N][N];
ll s1[N][N],d1[N],d2[N],_[N],f[2][N][N];
inline void Dij(int S,int&tot,ll *dis){
	int i,j,x;ll mi;tot=0;
	for(i=1;i<=n;++i)dis[i]=INF,used[i]=0;dis[S]=0;
	for(i=1;i<=n;++i){
		for(x=0,mi=INF,j=1;j<=n;++j)if(!used[j]&&dis[j]<mi)mi=dis[j],x=j;
		for(used[x]=1,_[++tot]=dis[x],j=1;j<=n;++j)if(g[x][j]<0x3f3f3f3f)dis[j]=min(dis[j],dis[x]+g[x][j]);
	}sort(_+1,_+tot+1);tot=unique(_+1,_+tot+1)-_-1;
	for(i=1;i<=n;++i)dis[i]=lower_bound(_+1,_+tot+1,dis[i])-_;
}
int main(void){
	int i,j,x,y,z;ll res;memset(g,0x3f,sizeof g);
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(i=1;i<=n;++i)scanf("%d",a+i),g[i][i]=0;
	while(m--)scanf("%d%d%d",&x,&y,&z),g[x][y]=g[y][x]=min(g[x][y],z);
	Dij(s,t1,d1),Dij(t,t2,d2);
	for(i=1;i<=n;++i)s1[d1[i]][d2[i]]+=a[i],++s2[d1[i]][d2[i]];
	for(i=t1;i;--i){
		for(j=t2;j;--j){
			s1[i][j]+=s1[i+1][j]+s1[i][j+1]-s1[i+1][j+1];
			if(s2[i][j])l[i][j]=i,r[i][j]=j;
			else l[i][j]=min((i==t1?t1:l[i+1][j]),(j==t2?t1:l[i][j+1])),r[i][j]=min((i==t1?t2:r[i+1][j]),(j==t2?t2:r[i][j+1]));
			f[0][i][j]=s1[i][j]-f[1][l[i][j]+1][j],f[1][i][j]=s1[i][j]-f[0][i][r[i][j]+1];
			if((i+j)^2)f[0][i][j]=min(f[0][i][j],f[0][i][j+1]),f[1][i][j]=min(f[1][i][j],f[1][i+1][j]);
		}
	}
	puts(!(res=2*f[0][1][1]-s1[1][1])?"Flowers":(res>0?"Break a heart":"Cry")); 
	return 0;
}
