#include<bits/stdc++.h>

using namespace std;

int a[5];

int main() {
    for(int i = 1; i <= 4; i++) scanf("%d", a + i);
    
    int d1 = a[2] - a[1], d2 = a[3] - a[2], d3 = a[4] - a[3];
    double q1 = (double)a[2] / a[1], q2 = (double)a[3] / a[2], q3 = (double)a[4] / a[3];
    
    if(d1 == d2 && d2 == d3) {
        printf("%d\n", a[4] + d1);
    } else if(q1 == q2 && q2 == q3) {
        double res = a[4] * q1;
        if(res == (int)res) printf("%d\n", (int)res);
        else printf("42\n");
    } else printf("42\n");
}