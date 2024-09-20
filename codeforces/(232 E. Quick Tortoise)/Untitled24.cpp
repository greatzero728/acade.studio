#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <utility>
#include <algorithm>
#define Fo(i,a,b) for(int i=(a);i<(b);++i)
#define Fr(i,a,b) for(int i=(a);i<=(b);++i)
#define Fl(i,a,b) for(int i=(a);i>=(b);--i)
#define Fe(i,x,y) for(int i=H[x][y];i;i=E[i].nx)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct FastIO
{
	template<typename T>
	FastIO& operator>>(T& x)
	{
		char c,l;
		for(c=0;!isdigit(c);c=getchar())l=c;
		for(x=0;isdigit(c);c=getchar())x=x*10-'0'+c;
		if(l=='-')x=-x;
		return *this;
	}	
}IO;

const int MX=510,MY=610000;

struct Query{int x,y,nx,ans;}E[MY];
int H[MX][MX],ec;
void Add(int xa,int ya,int xb,int yb)
{
	E[++ec].x=xa,E[ec].y=ya,E[ec].nx=H[xb][yb],H[xb][yb]=ec;
}

int N,M,Q;
char S[MX][MX];


#define A_(j) ((j)>>6)
#define B_(j) ((j)&63)
struct Bitset
{
	ull x[MX][8];
	void set(int i,int j)
	{
		x[i][A_(j)]|=1ull<<B_(j);
	}
	int get(int i,int j)
	{
		return (x[i][A_(j)]>>B_(j))&1;
	}
	void clear()
	{
		memset(x,0,sizeof(x));
	}
}B[2][MX];

void Merge(Bitset& c,Bitset& a,Bitset& b,int n,int m)
{
	int m_=A_(m);
	Fr(i,1,n)Fr(j,0,m_)
		c.x[i][j]=a.x[i][j]|b.x[i][j];
}



void Solve()
{
	Bitset *a=B[0],*b=B[1];
	Fr(i,1,N)
	{
		Fr(j,1,M)
		{
			if(S[i][j]=='#')b[j].clear();
			else Merge(b[j],a[j],b[j-1],i,j),b[j].set(i,j);
			
			/*printf("(%d,%d)\n",i,j);
			Fr(ii,1,N)
			{
				Fr(jj,1,M)printf("%d",b[j].get(ii,jj));
				putchar('\n');
			}*/
			
			Fe(k,i,j)E[k].ans=b[j].get(E[k].x,E[k].y);
		}
		swap(a,b);
	}
}


int main()
{
	IO>>N>>M;
	Fr(i,1,N)scanf("%s",S[i]+1);
	IO>>Q;
	int xa,ya,xb,yb;
	Fr(i,1,Q)
	{
		IO>>xa>>ya>>xb>>yb;
		Add(xa,ya,xb,yb);
	}
	Solve();
	Fr(i,1,Q)printf(E[i].ans?"Yes\n":"No\n");
	return 0;
}
