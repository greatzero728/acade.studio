#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;

long long mod_pow(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

struct Matrix {
    int data[3][3];
    Matrix() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                data[i][j] = 0;
            }
        }
    }
    Matrix operator*(const Matrix &other) {
        Matrix res;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    res.data[i][j] = (res.data[i][j] + 1LL * data[i][k] * other.data[k][j]) % (MOD - 1);
                }
            }
        }
        return res;
    }
};

int main() {
    long long n, f1, f2, f3, c;
    cin >> n >> f1 >> f2 >> f3 >> c;
    Matrix A;
    A.data[0][0] = A.data[0][1] = A.data[0][2] = A.data[1][0] = A.data[2][1] = 1;
    Matrix res;
    res.data[0][0] = res.data[1][1] = res.data[2][2] = 1;
    
    long long N = n;
    n -= 3;
    while (n) {
        if (n & 1) res = res * A;
        A = A * A;
        n >>= 1;
    }
    long long res00 = res.data[0][0], res01 = res.data[0][1], res02 = res.data[0][2];
    long long c_pow = (1LL * res02 + 2LL * res01 + 3LL * res00 - (N % (MOD - 1)) + (MOD - 1)) % (MOD - 1);
    long long c_val = mod_pow(c, c_pow);
    long long f1_val = mod_pow(f1, res02);
    long long f2_val = mod_pow(f2, res01);
    long long f3_val = mod_pow(f3, res00);
    long long f_n = c_val * f1_val % MOD * f2_val % MOD * f3_val % MOD;
    cout << f_n << endl;
}