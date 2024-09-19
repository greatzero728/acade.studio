#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010;
const double pi = acos(-1), eps = 1e-5;

double val[MAXN];
int N, cases;

void solve() {
    for(int f1 = 400; f1 <= 600; f1++) {
        for(int f2 = 400; f2 <= 600; f2++) {
            bool is_valid = true;
            for(int i = 1; i <= N; i++) {
                if(fabs(sin(pi / 180 * f1 * i / N) + sin(pi / 180 * f2 * i / N) - val[i]) < eps) continue;
                is_valid = false; break;
            }
            if(is_valid) {
                cout<<"Case "<<++cases<<", f1 = "<<f1<<", f2 = "<<f2<<endl;
                return;
            }
        }
    }
}

int main() {
    while(scanf("%d", &N), N) {
        for(int i = 1; i <= N; i++) scanf("%lf", val + i);
        solve();
    }
}