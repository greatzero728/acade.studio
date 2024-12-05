#include<bits/stdc++.h>

using namespace std;

int Partition(int *A, int p, int r) {
    int x = A[r];
    int i = p - 1;
    for(int j = p; j <= r - 1; j++) {
        if(A[j] <= x) {
            i = i + 1;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

int A[101010];

int main() {
    int n; scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", A + i);
    
    int id = Partition(A, 1, n);
    
    for(int i = 1 i <= n; i++) {
        if(i > 1) putchar(' ');
        if(i == id) printf("[");
        printf("%d", A[i]);
        if(i == id) printf("]");
    }
    return 0;
}