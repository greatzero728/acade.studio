#include <bits/stdc++.h>

using namespace std;


int main() {
    int n,m;
    cin >> n >> m;
    char a[n][m];
    int ex_x,ex_y,st_x,st_y;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> a[i][j];
            if(a[i][j]=='S'){
                st_x=i;
                st_y=j;
            }
            if(a[i][j]=='E'){
                ex_x=i;
                ex_y=j;
            }
        }
    }
    
    int dx[]={0,0,1,-1};
    int dy[]={1,-1,0,0};
    int dist[n][m];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            dist[i][j]=INT_MAX;
        }
    }
    dist[ex_x][ex_y]=0;
    queue<pair<int,int>> q;
    q.push({ex_x,ex_y});
    while(!q.empty()){
        int x=q.front().first;
        int y=q.front().second;
        q.pop();
        for(int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(nx>=0 && nx<n && ny>=0 && ny<m && a[nx][ny]!='T' && dist[nx][ny]==INT_MAX){
                dist[nx][ny]=dist[x][y]+1;
                q.push({nx,ny});
            }
        }
    }
    
    int ans=0;
    for(int i = 0;i<n;i++) {
        for(int j = 0;j<m;j++) {
            if(a[i][j] == 'T' || a[i][j] == 'S' || a[i][j] == 'E') continue;
            if(dist[i][j] <= dist[st_x][st_y]) {
                ans += a[i][j] - '0';
            }
        }
    }
    cout << ans;
    
    return 0;
}
