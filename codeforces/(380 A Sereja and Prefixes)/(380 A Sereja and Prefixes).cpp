#include<bits/stdc++.h>

using namespace std;
using INT = long long;

const int NN = 101010;

int tp[NN];
INT b[NN], c[NN], len[NN]; 

int main() {
	int m; scanf("%d",&m);
	for(int i = 0; i < m; i++) {
		scanf("%d", tp + i);
		if(tp[i] == 1) {
			scanf("%d", b + i);
			len[i + 1] = len[i] + 1;
		}
		else {
			scanf("%d %d", b + i, c + i);
			len[i + 1] = len[i] + (INT)b[i] * c[i];
		}
	}
    
	int n; scanf("%d", &n);
	while(n--) {
		INT i; scanf("%lld", &i);
        while(1) {
			int pos = lower_bound(len, len + m, i)-len;
			if(tp[pos - 1] == 1) {
                printf("%lld ", b[pos - 1]);
                break;
            }            
			i = (i - len[pos - 1] - 1) % b[pos - 1] + 1;
		}
    }
	return 0;
}