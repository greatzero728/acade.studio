#include <bits/stdc++.h>

using namespace std;

vector<int> mul(vector<int> &a, vector<int> &b) {
    int n = a.size();
    vector<int> ans(n);
    for (int i = 0; i < n; i++) ans[i] = a[b[i]];
    return ans;
}

vector<int> qpow(vector<int> a, int b) {
    int n = a.size();
    vector<int> ans(n);
    iota(ans.begin(), ans.end(), 0);
    for (; b; b >>= 1) {
        if (b & 1) ans = mul(a, ans);
        a = mul(a, a);
    }
    return ans;
}

using cd = complex<double>;
const double PI = acos(-1);

//void fft(vector<cd> & a, bool invert) {
//    int n = a.size();
//    if (n == 1)
//        return;
//
//    vector<cd> a0(n / 2), a1(n / 2);
//    for (int i = 0; 2 * i < n; i++) {
//        a0[i] = a[2*i];
//        a1[i] = a[2*i+1];
//    }
//    fft(a0, invert);
//    fft(a1, invert);
//
//    double ang = 2 * PI / n * (invert ? -1 : 1);
//    cd w(1), wn(cos(ang), sin(ang));
//    for (int i = 0; 2 * i < n; i++) {
//        a[i] = a0[i] + w * a1[i];
//        a[i + n/2] = a0[i] - w * a1[i];
//        if (invert) {
//            a[i] /= 2;
//            a[i + n/2] /= 2;
//        }
//        w *= wn;
//    }
//}
//vector<int> multiply(vector<int> const& a, vector<int> const& b) {
//    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
//    int n = 1;
//    while (n < a.size() + b.size()) 
//        n <<= 1;
//    fa.resize(n);
//    fb.resize(n);
//
//    fft(fa, false);
//    fft(fb, false);
//    for (int i = 0; i < n; i++)
//        fa[i] *= fb[i];
//    fft(fa, true);
//
//    vector<int> result(n);
//    for (int i = 0; i < n; i++)
//        result[i] = round(fa[i].real());
//    return result;
//}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string s;
    cin >> s;
    int n = s.length();
    int m;
    cin >> m;
    while (m--) {
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        int d, k;
        cin >> k >> d;
        int t = 0;
        for (int i = 0; i < d; i++) {
            for (int j = i; j < k; j += d)
                p[t++] = j;
        }
        vector<int> r(n);
        for (int i = 0; i < n; i++) r[i] = (i + 1) % n;
        vector<int> ans = qpow(mul(p, r), n - k + 1);
        for (int i = 0; i < n; i++) p[i] = (i - (n - k + 1) + n) % n;
        p = mul(ans, p);
        string ss = s;
        for (int i = 0; i < n; i++) ss[i] = s[p[i]];
        cout << ss << "\n";
        s = ss;
    }
    return 0;
}