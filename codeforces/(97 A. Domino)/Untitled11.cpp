#include <vector> 
#include <list> 
#include <map> 
#include <set> 
#include <deque> 
#include <queue> 
#include <stack> 
#include <bitset> 
#include <algorithm> 
#include <functional> 
#include <numeric> 
#include <utility> 
#include <sstream> 
#include <iostream> 
#include <iomanip> 
#include <cstdio> 
#include <cmath> 
#include <cstdlib> 
#include <cctype> 
#include <string> 
#include <cstring> 
#include <ctime> 

using namespace std;

char a[50][50];
int dd[50];
int d[50];
int ind[50][50];
int ans;
vector<pair<pair<int,int>,pair<int,int> > > bl;
int cc[50];
int cnt[10][10];

void search(int x)
{
	int i,j,xx,yy,b1;
	if (x==7)
	{
		b1=1;
		memset(cnt,0,sizeof(cnt));
		for (i=0;i<28;i++)
		{
			xx=d[ind[bl[i].first.first][bl[i].first.second]];
			yy=d[ind[bl[i].second.first][bl[i].second.second]];
			if (cnt[xx][yy]!=0)
			{
				b1=0;
				break;
			}
			cnt[xx][yy]++;
			cnt[yy][xx]++;
		}
		if (b1==1)
		{
			ans++;
			if (ans==1)
			{
				memcpy(dd,d,sizeof(d));
			}
		}
		return;
	}
	for (j=0;j<14;j++)
		if (d[j]==-1) break;
	d[j]=x;
	for (i=j+1;i<14;i++)
		if (d[i]==-1)
		{
			d[i]=x;
			search(x+1);
			d[i]=-1;
		}
	d[j]=-1;
}

int main()
{
	int i,j,tmp,m,n,nn;
	scanf("%d%d",&m,&n);
	for (i=0;i<m;i++)
		scanf("%s",a[i]);
	memset(ind,-1,sizeof(ind));
	nn=0;
	for (i=0;i<m;i++)
		for (j=0;j<n;j++)
			if ((a[i][j]!='.')&&(ind[i][j]==-1))
			{
				ind[i][j]=nn;
				ind[i+1][j]=nn;
				ind[i][j+1]=nn;
				ind[i+1][j+1]=nn;
				nn++;
			}
	memset(cc,0,sizeof(cc));
	bl.clear();
	for (i=0;i<28;i++) bl.push_back(make_pair(make_pair(0,0),make_pair(0,0)));
	for (i=0;i<m;i++)
		for (j=0;j<n;j++)
			if (a[i][j]!='.')
			{
				if ((a[i][j]>='a')&&(a[i][j]<='z')) tmp=a[i][j]-'a';
				else tmp=a[i][j]-'A'+26;
				if (cc[tmp]==0) bl[tmp].first=make_pair(i,j);
				else bl[tmp].second=make_pair(i,j);
				cc[tmp]++;
			}
	memset(d,-1,sizeof(d));
	search(0);
	printf("%d\n",ans*7*6*5*4*3*2);
	for (i=0;i<m;i++)
		for (j=0;j<n;j++)
			if (ind[i][j]!=-1)
				a[i][j]=dd[ind[i][j]]+'0';
	for (i=0;i<m;i++)
		printf("%s\n",a[i]);
	return 0;
}

