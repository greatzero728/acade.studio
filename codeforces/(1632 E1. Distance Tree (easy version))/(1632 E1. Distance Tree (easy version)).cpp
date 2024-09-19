#include<bits/stdc++.h>

using namespace std;

const int NN = 3030;

vector<int> adj[NN];

int dst[NN][NN], rt;

void calc_dist(int u, int f = 0) {
	for(int v : adj[u]) if(v != f) {
		dst[rt][v] = dst[rt][u] + 1;
		calc_dist(v, u);
	}
}

int n;

bool can(int x, int h) {
	vector<int> vec;
	for(int i = 1; i <= n; i++) {
		if(dst[1][i] > h) vec.push_back(i);
	}
	if(vec.empty()) return true;
	
	int mx = -1, A = vec[0], B;
	for(int u : vec) if(dst[A][u] > mx) {
		mx = dst[A][u], B = u;
	}
	mx = -1;
	for(int u : vec) if(dst[B][u] > mx) {
		mx = dst[B][u], A = u;
	}
	return x + (dst[A][B] + 1 >> 1) <= h;
}

int main() {
	
    int t; scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) adj[i].clear();
        for(int i = 1, u, v; i < n; i++) {
            scanf("%d %d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        for(int i = 1; i <= n; i++) {
        	dst[rt = i][rt] = 0, calc_dist(rt);
        }
        
        for(int x = 1; x <= n; x++) {
        	int st = 0, ed = n;
        	while(ed - st > 1) {
        		int md = st + ed >> 1;
        		if(can(x, md)) ed = md;
        		else st = md;
        	}
        	printf("%d ", ed);
        }
        puts("");
    }
}