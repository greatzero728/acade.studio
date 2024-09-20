#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using pii = pair<int, int>;
using ppp = pair<pii, pii>;

static char fjf[1010];
char gc() {
	static char *L = fjf, *R = L;
	if(L == R) {
		int n = fread(fjf, 1, 1010, stdin);
		if(!n) return -1; L = fjf, R = L + n;
	}
	return *L++;
}
void gn(int &x) {
    char c; while(c = gc(), (c < 48 || 57 < c) && ~c);
	for(x = c - 48; c = gc(), 48 <= c && c <= 57; x = 10 * x + c - 48);
}
bool gn(char &c) {while(c = gc(), ~c && isspace(c)); return ~c;}
bool gn(char *s) {
	char c; while(c = gc(), ~c && isspace(c)); if(!~c) return 0;
	for(*s++ = c; c = gc(), ~c && !isspace(c); *s++ = c); return *s = 0, 1;
}

const int NN = 505, MM = 606060;

char s[NN][NN];
vector<ppp> query[NN];

bool ans[MM];

int main() {
    int n, m; gn(n), gn(m);
    for(int i = 1; i <= n; i++) gn(s[i] + 1);
    int q; gn(q);
    
    for(int i = 1; i <= q; i++) {
        int x1, y1, x2, y2; gn(x1), gn(y1), gn(x2), gn(y2);
        query[x1].push_back({{i, y1}, {x2, y2}});
    }
    
    bitset<501> can[m + 1][n + 1];
    for(int xmn = n; xmn >= 1; xmn--) {
        for(int ymn = m; ymn >= 1; ymn--) {
            if(s[xmn][ymn] == '.') {
                can[ymn][xmn].set(ymn);
                if(s[xmn][ymn + 1] == '.') {
                    for(int x = xmn; x <= n; x++) {
                        can[ymn][x] = can[ymn][x] | can[ymn + 1][x];
                    }
                }
            }
            else {
                for(int x = xmn; x <= n; x++) {
                    can[ymn][x].reset();
                }
            }
        }
        for(ppp p : query[xmn]) {
            ans[p.x.x] = can[p.x.y][p.y.x][p.y.y];
        }
    }
    for(int i = 1; i <= q; i++) {
        if(ans[i]) puts("Yes");
        else puts("No");
    }
}