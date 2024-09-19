#include"bits/stdc++.h"
using namespace std;
void ext()
{
    cout<<"IMPOSSIBLE"<<endl;
    exit(0);
}
char s[10];
vector<int>a[1000005][2];
vector<int>ans;
int solve(int i,int n)
{
    if(i>n)return i-1;
    int lx=0,rx=n;
    for(auto j:a[i][0])lx=max(lx,j);
    int now=solve(i+1,lx);
    ans.push_back(i);
    for(auto j:a[i][1])
    {
        if(j<=now)ext();
        rx=max(rx,j);
    }
    now=solve(now+1,rx);
    return now;
}
int main()
{
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=k;i++)
    {
        int x,y;
        scanf("%d%d%s",&x,&y,s);
        if(x>=y)ext();
        int op;
        if(s[0]=='L')op=0;
        else op=1;
        a[x][op].push_back(y);
    }
    solve(1,n);
    for(int i=0;i<n;i++)printf("%d%c",ans[i]," \n"[i==n-1]);
    return 0;
}