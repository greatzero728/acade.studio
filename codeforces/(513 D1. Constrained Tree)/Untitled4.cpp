#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n,c,a[100011],b[100011],typ[100011],lst[111][111],dp[111][111];char s[11];
bool dfs(int x,int n)
{
	if(~dp[x][n])return dp[x][n];
	if(!n)return 1;
	for(int i=1;i<=c;++i)if(a[i]==x)if(n<b[i]-a[i]+1||b[i]-a[i]+1<=1)return 0;
	int mn=n-1,mx=0;
	for(int i=1;i<=c;++i)if(a[i]==x)
	{
		if(typ[i]==1)
		{
			mx=max(mx,b[i]-a[i]);
		}
		else mn=min(mn,b[i]-a[i]-1);
	}
	for(int j=mx;j<=mn;++j)
	{
		if(dfs(x+1,j)&&dfs(x+j+1,n-1-j))
		{
			dp[x][n]=1;lst[x][n]=j;return 1;
		}
	}
	return dp[x][n]=0;
}
void print(int x,int cur)
{
	if(!cur)return;
	print(x+1,lst[x][cur]);
	printf("%d ",x);
	print(x+lst[x][cur]+1,cur-1-lst[x][cur]);
}
int main()
{
	scanf("%d%d",&n,&c);for(int i=1;i<=c;++i){
        scanf("%d%d%s",a+i,b+i,s+1);
        if(a[i]==b[i]){printf("IMPOSSIBLE\n");return 0;}
        if(s[1]=='L')typ[i]=1;
        else typ[i]=2;
    }
	memset(dp,-1,sizeof(dp));
	if(!dfs(1,n))printf("IMPOSSIBLE\n");
	else
	{
		print(1,n);putchar(10);
	}return 0;
}