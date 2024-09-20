#include<bits/stdc++.h>
#define up(a,b,c) for(int a=b;a<=c;++a)
#define dn(a,b,c) for(int a=b;a>=c;--a)
const int N=551,Q=66e4;
using namespace std;
int n,m,q,res[Q];
struct qry
{
	int x1,y1,x2,y2,id;
	bool operator < (const qry &b) const
	{
		return b.x1<x1;
	}
	void read(int i)
	{
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2),id=i; 
	}
}e[Q];
char s[N][N];
bitset<N>f[N][N];
int main()
{
	scanf("%d%d",&n,&m);
	up(i,1,n)
		scanf("%s",s[i]+1);
	scanf("%d",&q);
	up(i,0,q-1)e[i].read(i);
	sort(e,e+q);
	int t=0;
	dn(i,n,1)
	{
		dn(j,m,1)
			if(s[i][j]=='#')
				up(a,i,n)f[j][a].reset();
			else
			{
				f[j][i][j]=1;
				if(s[i][j+1]!='#')
					up(a,i,n)
						f[j][a]|=f[j+1][a];
			}
		while(t<q&&e[t].x1==i)
			res[e[t].id]=int(f[e[t].y1][e[t].x2][e[t].y2]),++t;
	}
	up(i,0,q-1)
		puts(res[i]?"Yes":"No");
	return 0;
} 