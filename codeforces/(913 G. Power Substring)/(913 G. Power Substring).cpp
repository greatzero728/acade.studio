#include<iostream>
using namespace std;

int main(){
    long long n; 
    cin >> n;
    while(n--){
        long long x, r = 1, l, k = 0;
        cin >> x;
        l = to_string(x).length();
        while(1){
            long long v = x, m = 1LL << (l + k);
            if (v % m) v += m - v % m; 
            if (v % 5 == 0) v += m;
            if (v % m == 0 && v % 5 && v - x < r){
                long long y = v >> (l + k), p, s = 5;
                p = (y % 5 == 0) ? -1 : (y % 5 == 1) ? 0 : (y % 5 == 2) ? 1 : (y % 5 == 3) ? 3 : 2;
                for(long long i = 1; i < l + k; i++){
                    while(1){
                        long long a = 1, b = 2, e = p, d = s * 5;
                        while(e){
                            if(e & 1){
                                long long c = 0, f = a, g = b;
                                while(g){if (g & 1) c = (c + f) % d; f = (f + f) % d; g >>= 1; }
                                a = c;
                            }
                            long long h = 0, j = b;
                            while(j){ if (j & 1) h = (h + b) % d; b = (b + b) % d; j >>= 1; }
                            b = h; e >>= 1;
                        }
                        if(a == y % (s * 5)) break;
                        p += s / 5 * 4;
                    }
                    s *= 5;
                }
                cout << p + l + k << endl;
                break;
            }
            x *= 10; r *= 10; k++;
        }
    }
    return 0;
}