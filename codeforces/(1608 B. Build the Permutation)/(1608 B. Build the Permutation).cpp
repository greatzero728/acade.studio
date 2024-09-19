#include<bits/stdc++.h>

using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, a, b; scanf("%d %d %d", &n, &a, &b);
        if(a + b > n - 2 || abs(a - b) > 1) {
            puts("-1");
            continue;
        }
        if(a == b + 1) {
            for(int i = 0; i <= b; i++) {
                printf("%d %d ", n - (2 * i + 1), n - (2 * i));
            }
            for(int i = n - (2 * b + 2); i >= 1; i--) {
                printf("%d ", i);
            }
            puts("");
        }
        if(a == b) {
            printf("1");
            for(int i = 1; i <= a; i++) {
                printf(" %d %d", 2 * i + 1, 2 * i);
            }
            for(int i = 2 * a + 2; i <= n; i++) {
                printf(" %d", i);
            }
            puts("");
        }
        if(a + 1 == b) {
            printf("%d 1", n);
            for(int i = 1; i <= a; i++) {
                printf(" %d %d", 2 * i + 1, 2 * i);
            }
            for(int i = 2 * a + 2; i < n; i++) {
                printf(" %d", i);
            }
            puts("");
        }
    }
}
