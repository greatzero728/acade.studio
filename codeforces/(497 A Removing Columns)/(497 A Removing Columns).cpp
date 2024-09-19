#include <bits/stdc++.h>

using namespace std;

const int NN = 121;

char s[NN][NN];
string vec[NN];

int main() {
    int n, m; scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++) scanf("%s", s[i]);
    
    int ans = 0;
    for(int j = 0; j < m; j++) {
        for(int i = 0; i < n; i++) {
			vec[i].clear();
			for(int k = 0; k <= j; k++) vec[i] += s[i][k];
		}
        bool sorted = 1;
        for(int i = 1; i < n; i++) if(vec[i - 1] > vec[i]) {sorted = 0; break;}
        if(!sorted) {
        	cerr<<j<<endl;
            for(int i = n; i--; ) for(int k = j; k + 1 < m; k++) s[i][k] = s[i][k + 1];
            ans++, m--, j--;
        }
    }
    printf("%d\n", ans);
    return 0;
}
