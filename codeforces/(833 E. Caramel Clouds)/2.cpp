#include <bits/stdc++.h>

#define pb push_back
#define x first
#define y second

using namespace std;
typedef long long INT;
typedef pair <int, int> pii;
typedef vector <int> VI;

#define NN (1<<19)

int n, C;
int none, mx;
int l[NN], r[NN], cost[NN];
int id[NN], pos[NN];
int ans[NN];

map <int, int> two[NN];
int one[NN];
int mx_with[NN];

struct RMQ_Tree{
	int n;
	int mx[1<<20];
	
	void init(int _n) {
		for(n=1; n<_n; n<<=1);
		for(int i=n<<1; --i; ) mx[i]=0;
	}
	void insert(int p, int val){
		p+=n-1;
		for( ; p && val>mx[p]; p>>=1) mx[p]=val;
	}
	int calc(int st, int ed){ // maximum of [st, ed]
		if(st>ed) return 0;
		st+=n-1; ed+=n;
		
		int ans=0;
		while(st<ed){
			if(st&1) ans=max(ans, mx[st++]);
			if(ed&1) ans=max(ans, mx[ed^1]);
			st>>=1; ed>>=1;
		}
		return ans;
	}
} Tree;

int main (){
#ifndef ONLINE_JUDGE
	freopen ("in.in", "r", stdin);
	freopen ("out.out", "w", stdout);
#endif
	
	cin >> n >> C;
	
	vector <pii> vec;
	for(int i=1; i<=n; i++){
		scanf("%d %d %d", l+i, r+i, cost+i);
		id[i]=i;
		vec.pb(pii(l[i], i));
		vec.pb(pii(r[i], -i));
	}
	
	sort(id+1, id+n+1, [](int u, int v){return cost[u]<cost[v];});
	for(int i=1; i<=n; i++) pos[id[i]]=i;
	
	vec.pb(pii(2000000000, 0));
	sort(vec.begin(), vec.end());
	
	int m;
	cin >> m;
	
	vector <pii> que;
	for(int i=0, p; i<m; i++){
		scanf("%d", &p);
		que.pb(pii(p, i));
	}
	
	sort(que.begin(), que.end());
	
	set <int> cloud;
	
	Tree.init(n);
	
	int now=0, cur=0;
	for(pii p : vec){
		int del=p.x-now;
		now=p.x;
		
		if(cloud.empty()) none+=del;
		else if(cloud.size()==1){
			int x=*cloud.begin();
			one[x]+=del;
			Tree.insert(pos[x], one[x]);
			if(cost[x]<=C){
				mx=max(mx, one[x]+mx_with[x]);
				int st=0, ed=n+1;
				while(ed-st>1){
					int mid=st+ed>>1;
					if(cost[id[mid]]+cost[x]<=C) st=mid;
					else ed=mid;
				}
				mx=max(mx, one[x]+Tree.calc(1, min(st, pos[x]-1)));
				mx=max(mx, one[x]+Tree.calc(pos[x]+1, st));
			}
		}
		else if(cloud.size()==2){
			int x=*cloud.begin();
			int y=*--cloud.end();
			two[x][y]+=del;
			two[y][x]+=del;
			if(cost[x]+cost[y]<=C){
				mx_with[x]=max(mx_with[x], two[x][y]+one[y]);
				mx_with[y]=max(mx_with[y], two[y][x]+one[x]);
				mx=max(mx, one[x]+one[y]+two[x][y]);
			}
		}
		
		while(cur<m && que[cur].x<=none+mx){
			ans[que[cur].y]=now-(none+mx-que[cur].x);
			cur++;
		}
		
		if(p.y>0) cloud.insert(p.y);
		else cloud.erase(-p.y);
	}
	
	for(int i=0; i<m; i++) printf("%d\n", ans[i]);
	
	return 0;
}

     