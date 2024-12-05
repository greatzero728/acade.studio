#include<bits/stdc++.h>
using namespace std;
#define MAX 6005

struct Data{
  int a,b,c;
  Data(){    a=b=c=-1;  }
  void insert(int x){
    if(a==x||b==x||c==x)return;
    c=b;
    b=a;
    a=x;
  }
  bool count(int x){
    return (a==x||b==x||c==x);
  }
  int size(){
    return (a>=0)+(b>=0)+(c>=0);
  }
  void erase(int x){
    if(a==x){
      a=b;b=c;c=-1;
    }else if(b==x){
      b=c;c=-1;
    }else if(c==x){
      c=-1;
    }
  }
};

int N,K;
vector<int> G[MAX];
Data g[MAX];

int f[MAX],bs[MAX];
bool visited[MAX];


int px[MAX],py[MAX];


bool dfs(int v){
  visited[v]=true;
  for(int i=0;i<(int)G[v].size();i++){
    int u=G[v][i];
    

    if(f[u]>(int)g[u].size()){
      g[v].insert(u);
      g[u].insert(v);
      return true;
    }
    
    for(int j=0;j<(int)G[u].size();j++){
      int w=G[u][j];
      if(g[u].count(w)==0)continue;
      
      if(!visited[w]&&dfs(w)){
        g[v].insert(u);
        g[u].insert(v);

        g[u].erase(w);
        g[w].erase(u);
        return true;
      }
    }
  }
  return false;
}

void rec(int v,int depth=0){
  if(bs[v]!=-1)return;
  bs[v]=depth%2;
  for(int i=0;i<(int)G[v].size();i++){
    rec(G[v][i],depth+1);
  }
}

int main(){
  cin>>N>>K;
  for(int i=0;i<N;i++){
    cin>>px[i]>>py[i];
    for(int j=0;j<i;j++){
      int X=px[i]-px[j];
      int Y=py[i]-py[j];
      if( abs(X) <=1 && abs(Y)<=1){
        G[i].push_back(j);
        G[j].push_back(i);
      }
    }
  }
  for(int i=0;i<N;i++){
    sort(G[i].begin(),G[i].end());
  }
  
  memset(bs,-1,sizeof(bs));
  for(int i=0;i<N;i++){
    rec(i);
  }
  
  fill(f,f+MAX,1);
  int maxflow=0;
  for(int i=0;i<N;i++){
    if(f[i]==(int)g[i].size())continue;
    memset(visited,false,sizeof(visited));
    if( dfs(i) )maxflow++;
  }
  
  if( N-maxflow < K ){
    cout<<-1<<endl;
    return 0;
  }

    bool ans[MAX]={};
  for(int v=0;v<N;v++){
    bool flg=false;
    for(int i=0;i<(int)G[v].size();i++){
      if( ans[G[v][i]] ){
        flg=true;
      }
    }
    if(flg)continue;
    f[v]=3;
    
    int c=0;
    while(1){
      memset(visited,false,sizeof(visited));
      int a=dfs(v);
      if(a==0)break;
      c++;
    }
    
    if( N - (maxflow+c)>= K ){
      ans[v]=true;
      maxflow+=c;
    }else{
      f[v]=1;
      while(g[v].size()>1){
        int u=g[v].a;
        g[u].erase(v);
        g[v].erase(u);
      }
    }
  }
  
  for(int i=0;i<N;i++){
    if(ans[i]&&K>0){
      cout<<i+1<<endl;
      K--;
    }
  }
  return 0;
}
