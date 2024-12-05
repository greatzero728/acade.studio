#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0; i<(int)(n); i++)
#define rep(i,n) for(int i=0; i<(int)(n); i++)
typedef complex<double> P;
typedef vector<P> L;
P input() {
    double x, y;
    cin >> x >> y;
    return P(x, y);
}
const double EPS = 1e-8;
int sign(double x) {
    if(x > EPS) return 1;
    if(x < -EPS) return -1;
    return 0;
}
double dot(P a, P b) {
    return real(conj(a) * b);
}
double cross(P a, P b) {
    return imag(conj(a) * b);
}
P vec(L l) {
    return l[1] - l[0];
}
bool iLS(L l, L s) {
    return sign(cross(vec(l), s[0] - l[0]) * cross(vec(l), s[1] - l[0])) <= 0;
}

vector<P> pLL(L l, L m) {
    double A = cross(vec(l), vec(m));
    double B = cross(vec(l), l[1] - m[0]);
    if(sign(A) == 0 && sign(B) == 0) return {l[0], l[1], m[0], m[1]};
    if(sign(A) == 0) return {};
    return {m[0] + vec(m) * B / A};
}
const double INF = 1e10;
namespace std{
    bool operator < (const P& a, const P& b) {
        if(a.real() != b.real()) return a.real() < b.real();
        else return a.imag() < b.imag();
    }
};

int cnt;
map< tuple<P, P, double>, double> memo;
double calc(P dog, P fix, double length, P G, const vector<P>& rod, set<P> used=set<P>()) {
    auto t = make_tuple(dog, fix, length);
    if(sign(abs(dog - G)) == 0) return 0;
    if(sign(length - abs(fix - G)) < 0) return INF;
    if(memo.count(t)) return memo[t];

    //cout << dog << " " << fix << endl;

    vector<P> search = rod;
    search.push_back(G);
    double res = INF;
    for(P to : search) if(abs(dog - to) > EPS) {
        L path = {dog, to};
        vector<pair<P, P>> cand;
        for(int i = 0; i < rod.size(); i++) {
            if(sign(abs(rod[i] - dog)) == 0) continue;
            L line = {fix, rod[i]};
            if(iLS(line, path)) {
                vector<P> cpv = pLL(line, path);
                if(cpv.size() > 1) continue; // is it right??
                P cp = cpv[0];
                if(dot(rod[i] - fix, cp - fix) < 0) continue;
                if(sign(abs(rod[i] - fix) - abs(cp - fix)) >= 0) continue;
                cand.push_back(make_pair(cp, rod[i]));
            }
        }

        if(cand.empty()){
            if(!used.count(to)) {
                set<P> used2 = used;
                used2.insert(to);
                res = min(res, abs(to - dog) + calc(to, fix, length, G, rod, used2));
            }
            continue;
        }

        sort(cand.begin(), cand.end(),
                [&](pair<P, P> c1, pair<P, P> c2) {
                    P p1, r1, p2, r2;
                    tie(p1, r1) = c1;
                    tie(p2, r2) = c2;
                    int sp = sign( abs(dog - p1) - abs(dog - p2) );
                    int sr = sign( abs(fix - r1) - abs(fix - r2) );
                    return sp < 0 || (sp == 0 && sr > 0);
                    });

        P ndog, nfix;
        tie(ndog, nfix) = cand[0];
        double nlength = length - abs(nfix - fix);
        //cout << "p1: " << dog << " " << fix << " " << length << "->" << 
        //    ndog << " " << nfix << " " << nlength << endl;
        res = min(res, abs(dog - ndog) + calc(ndog, nfix, nlength, G, rod, used));
        //cout << "p2: " << dog << " " << fix << " " << length << "->" << 
        //    nfix << " " << fix << " " << length << endl;
        if(!used.count(nfix)){
            set<P> used2 = used;
            used2.insert(nfix);
            res = min(res, abs(dog - nfix) + calc(nfix, fix, length, G, rod, used2));
        }
    }
    return memo[t] = res;
}
int main() {
    int n;
    while(cin >> n && n > 0) {
        P dog = input();
        P goal = input();
        P fix = {0, 0};
        vector<P> rod(n);
        REP(i, n) rod[i] = input();
        memo.clear();
        double ans = calc(dog, fix, abs(dog - fix),goal, rod);
        if(ans >= INF) {
            cout << -1 << endl;
        } else {
            printf("%.7f\n", ans);
        }
    }
    return 0;
}
