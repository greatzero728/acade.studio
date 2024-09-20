#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define fo(i,a,b) for (int i = a; i <= b; ++i)
#define fd(i,a,b) for (int i = a; i >= b; --i)
#define fe(i,x) for (int i = g[x], y = E[i].y; i; i = E[i].l, y = E[i].y)
#define forall(i, x) for (typeof((x).begin()) i = (x).begin(); i != (x).end(); ++i)
#define pb push_back
#define SIZE(x) ((int) (x).size())
#define MP make_pair
#define fi first
#define se second
#define UNIQUE(x) x.resize(unique(x.begin(), x.end()) - x.begin())
#define clr(a,x) memset(&a, x, sizeof(a))
#define move(a,b) memcpy(&b, &a, sizeof(a))
#define Plus(a,b) (((ll) (a) + (b)) % mo)
#define Minus(a,b) ((((ll) (a) - (b) ) % mo + mo) % mo)
#define Mul(a,b) ((ll) (a) * (b) % mo)
#define updmin(a,b) (a = min(a, b))
#define updmax(a,b) (a = max(a, b))
#define sqr(x) ((x) * (x))

const int ml=510, mo=(int)1e8;
int len(0);
struct high{
    int n, a[ml];
    high(){ clr(a, 0), n = 1; }
    high(int x){
        clr(a, 0), n = 0;
        do { a[++n] = x % mo, x /= mo; } while (x);
    }
    void init(int x){
        clr(a, 0), n = 0;
        do { a[++n] = x % mo, x /= mo; } while (x);
    }

    void cut(){
        updmax(len, n);
        while (n > 1 && !a[n]) --n;
    }

    int cmp(high p){
        if (n > p.n) return 1;
        if (n < p.n) return -1;
        fd (i, n, 1) if (a[i] > p.a[i]) return 1;
        else if (a[i] < p.a[i]) return -1;
        return 0;
    }
    void add(int d){
        int g = d; ++n;
        fo (i, 1, n){
            if (!g) break;
            g += a[i], a[i] = g % mo, g /= mo;
        }
        cut();
    }
    void mul(int d){
        ll g = 0; n += 2;
        fo (i, 1, n) g = (ll) a[i] * d + g, a[i] = g % mo, g /= mo;
        cut();
    }
    void div(int d){
        int g = 0;
        fd (i, n, 1) g = g * mo + a[i], a[i] = g / d, g %= d;
        cut();
    }
    high operator +(high p){
        high ret; ret.init(0);
        int g = 0; ret.n = max(n, p.n) + 1;
        fo (i, 1, ret.n) g += a[i] + p.a[i], ret.a[i] = g % mo, g /= mo;
        ret.cut();
        return ret;
    }
    high operator -(high p){
        high ret; ret.init(0);
        int g = 0; ret.n = n;
        fo (i, 1, ret.n){
            ret.a[i] = g + a[i] - p.a[i];
            if (ret.a[i] < 0) g = -1, ret.a[i] += mo; else g = 0;
        }
        ret.cut();
        return ret;
    }
    high operator /(high p){
        high d, R, tmp; d.init(0), R.init(0);
        d.n = n;
        fd (i, n, 1){
            R.mul(mo);
            R.add(a[i]);
            int l = 0, r = mo - 1;
            while (l <= r){
                int m = (l + r) / 2;
                high t = p;
                t.mul(m);
                int c = R.cmp(t);
                if (!c){
                    d.a[i] = m;
                    break;
                }
                if (c > 0) d.a[i] = m, l = m + 1;
                else r = m - 1;
            }
            high t = p;
            t.mul(d.a[i]);
            R = R - t;
        }
        d.cut();
        return d;
    }

    void print(){
        printf("%d", a[n]);
        fd (i, n - 1, 1) printf("%08d", a[i]);
    }
};

high GCD(high a, high b){
    int Cnt = 0, two = 0;
    while (b.n > 1 || b.a[1]){
        while (!(a.a[1] & 1) && !(b.a[1] & 1))
            a.div(2), b.div(2), ++two;
        while (!(a.a[1] & 1)) a.div(2);
        while (!(b.a[1] & 1)) b.div(2);
        if (a.cmp(b) > 0) swap(a, b);
        b = b - a;
    }
    while (two) a.mul(2);
    return a;
}



int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    ll n; cin>>n;
    ll x = 0;
    while(n%2==0){
        n/=2;
        x++;
    }
    if(n==1){
        cout << x << "/1";
        return 0;
    }

    int k = 0, m = 1;
    high ans;
    ans.init(0);
    do {
        ++k, m <<= 1;
        ans.mul(2);
        if (m > n){
            m -= n;
            ans.add(k);
        }
    } while (m > 1);

    ans.mul(n);
    ans.add(k);

    high b,gc,c;
    b.init(1);
    for(int i=0; i<k; i++) {
        b.mul(2);
    }
    b = b-*(new high(1));
    gc = GCD(ans,b);
    ans= ans/gc;
    b = b/gc;
    c = b;
    b.mul(x);
    ans = ans + b;
    ans.print();
    printf("/");
    c.print();
}