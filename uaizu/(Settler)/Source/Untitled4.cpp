#include<bits/stdc++.h>
using namespace std;
#define MAX_V 6005
#define INF (1e9)
using namespace std;
typedef long long ll;

struct edge{int to, cap, rev;};

vector<edge> G[MAX_V];
bool used[MAX_V];

void add_edge(int from,int to,int cap){
  G[from].push_back((edge){to,cap,(int)G[to].size()});
  G[to].push_back((edge){from,0,(int)G[from].size()-1});  
}

int dfs(int v,int t,int f,int cnt=INF){
  if(v == t)return f;
  if(!cnt)return 0;
  used[v]=true;
  for(int i=0; i<G[v].size() ;i++){
    edge &e = G[v][i];
    if(!used[e.to] && e.cap > 0){
      int d = dfs(e.to ,t , min(f,e.cap),cnt-1);
      if(d > 0){
	e.cap -= d;
	G[e.to][e.rev].cap += d;
	return d;
      }
    }
  }
  return 0;
}

int max_flow(int s,int t){
  int flow = 0;
  for(;;){
    memset(used,0,sizeof(used));
    int f = dfs(s, t, INF);
    if(f == 0)return flow;
    flow += f;
  }
}

void flow_rev(int s,int t,int f){
  while(f){
    memset(used,0,sizeof(used));
    f-=dfs(s,t,f,2);
  }
}

ll n,k,x[MAX_V],y[MAX_V],s,t;

bool check_dis(int A,int B){
  return (x[A]-x[B])*(x[A]-x[B])+(y[A]-y[B])*(y[A]-y[B])<4;
}

void make_graph(){
    
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      if(i!=j&&y[i]%2&&!(y[j]%2)&&check_dis(i,j))add_edge(i,j,INF);

  s=n, t=n+1;
  for(int i=0;i<n;i++)
    if(y[i]%2)add_edge(s,i,1);
    else add_edge(i,t,1);
  
}

vector<int> ans;

void solve(){
  int F=max_flow(s,t);
  
  if(n-F<k){
    cout<<-1<<endl;
    return;
  }

  for(int i=0;i<n;i++){
    
    if(y[i]%2){
      int idx;
      for(int j=0;j<G[s].size();j++)
	if(G[s][j].to==i)idx=j,G[s][j].cap+=INF;
      
      int add_F=max_flow(s,t);
      if(n-(F+add_F)>=k)ans.push_back(i+1),F+=add_F;
      else{
	edge &e=G[s][idx];
	e.cap-=INF-add_F;
	G[e.to][e.rev].cap-=add_F;
	
	flow_rev(t,i,add_F);
      }
      
    }else{
      int idx;
      for(int j=0;j<G[i].size();j++)
	if(G[i][j].to==t)idx=j,G[i][j].cap+=INF;
      
      int add_F=max_flow(s,t);
      if(n-(F+add_F)>=k)ans.push_back(i+1),F+=add_F;
      else{
	edge &e=G[i][idx];
	e.cap-=INF-add_F;
	G[e.to][e.rev].cap-=add_F;
	
	flow_rev(i,s,add_F);
      }
      
    }
    
  }
  for(int i=0;i<k;i++)cout<<ans[i]<<endl;
}

int main(){
  cin>>n>>k;
  for(int i=0;i<n;i++)cin>>x[i]>>y[i];
  
  make_graph();

  solve();
  
  return 0;
}
