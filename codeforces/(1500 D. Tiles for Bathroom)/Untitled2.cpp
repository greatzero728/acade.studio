#include<bits/stdc++.h>
#define pb push_back
#define fors(i, a, b) for(int i = (a); i < (b); ++i)
#define P pair<int,int>
using namespace std;
int a[1555][1555], vis[2500000],n,q,d[1555];
vector<P> col[1555][1555],t;
void sol(int x, int y){
    t.pb(P(0,a[x][y]));
    if(x>1) for(P p:col[x-1][y]) t.pb(p);
    if(y>1) for(P p:col[x][y-1]) t.pb(p);
    if(x>1&&y>1) for(P p:col[x-1][y-1]) t.pb(p);
    sort(t.begin(),t.end());
    for(P p:t) { p.first++;
        if(!vis[p.second]) vis[p.second]=1,col[x][y].pb(p);
        if(col[x][y].size()>q) break;
    }for(P p:col[x][y]) vis[p.second] = 0; t.clear();
}
int main()
{
    cin>>n>>q;
    fors(i,1,n+1) fors(j,1,n+1) {
        scanf("%d",&a[i][j]),sol(i, j);
        int r = min(i,j);
        if(col[i][j].size()>q) r = min(col[i][j][q].first-1, r);d[1]++;d[r+1]--;
    }
    fors(i,1,n+1)d[i]+=d[i-1],printf("%d\n", d[i]);
	return 0;
}

