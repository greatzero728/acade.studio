#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using pii = pair<int, int>;
using ppi = pair<pii, int>;
using INT = long long;

const int NN = 101010;

char s[NN];

const int _mx = 17;

ppi pos[NN];
int Rank[NN], sa[NN], H[NN];

void build_suf(char *s, int n) {
	int i, j = n, cnt, u;
	while(j--) Rank[j] = s[j]; pos[n] = {{-1, -1}, -1};
	Rank[n] = 0;
	while(++j < _mx) {
		i = n, cnt = 0;
		while(i--) pos[i] = {{Rank[i], Rank[min(n, i + (1 << j))]}, i};
		sort(pos, pos + n);
		while(++i < n) {
			Rank[pos[i].y] = cnt + 1;
			if(pos[i].x != pos[i + 1].x) cnt++;
		}
		if(cnt == n) break;
	}
    while(i--) sa[Rank[i]] = i;
}

void Height(char *s, int n) {
	for(int i = 0, j, h = 0; i < n; i++) if(Rank[i] > 1) {
		h = max(0, h - 1), j = sa[Rank[i] - 1];
		while(i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
		H[Rank[i]] = h;
	}
}

stack<ppi> st;

int main() {
    scanf("%s", s);
    int n = strlen(s);
    build_suf(s, n);
    Height(s, n);
    
    INT ans = 0, S = n;
    st.push({{1, n}, 1});
    
    for(int j = 1; j <= n; j++) {
        int height = H[j];
        if(j == 1) height = n - sa[1];
        
        while(!st.empty()) {
	        int ST = st.top().x.x, ED = st.top().x.y, val = st.top().y;
	        if(height < ST) {
                st.pop();
                S -= (INT)(ED - ST + 1) * val;
            }
	        else {
				if(height < ED) {
                    st.top().x.y = height;
                    S -= (INT)(ED - height) * val;
                }
	        	break;
	        }
	    }
	    st.push({{height + 1, n}, j});
        S += (INT)(n - height) * j;
		ans += (INT)j * n - S + j;
    }
    printf("%lld\n", ans);
}