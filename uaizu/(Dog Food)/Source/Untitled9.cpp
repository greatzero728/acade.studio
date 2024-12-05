#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <queue>
#include <stack>
#include <algorithm>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <deque>
#include <complex>
#include <string>
#include <iomanip>
#include <sstream>
#include <bitset>
#include <valarray>
#include <iterator>
using namespace std;
typedef long long int ll;
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define REP(i,x) for(int i=0;i<(int)(x);i++)
#define FOR(i,c) for(__typeof((c).begin())i=(c).begin();i!=(c).end();i++)
#define RREP(i,x) for(int i=((int)(x)-1);i>=0;i--)
#define RFOR(i,c) for(__typeof((c).rbegin())i=(c).rbegin();i!=(c).rend();i++)
#define ALL(container) container.begin(), container.end()
#define RALL(container) container.rbegin(), container.rend()
#define SZ(container) ((int)container.size())
#define mp(a,b) make_pair(a, b)
#define UNIQUE(v) v.erase( unique(v.begin(), v.end()), v.end() );

template<class T> bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T> bool chmin(T &a, const T &b) { if (a>b) { a=b; return 1; } return 0; }
template<class T> ostream& operator<<(ostream &os, const vector<T> &t) {
os<<"["; FOR(it,t) {if(it!=t.begin()) os<<","; os<<*it;} os<<"]"; return os;
}
template<class T> ostream& operator<<(ostream &os, const set<T> &t) {
os<<"{"; FOR(it,t) {if(it!=t.begin()) os<<","; os<<*it;} os<<"}"; return os;
}
template<class S, class T> ostream& operator<<(ostream &os, const pair<S,T> &t) { return os<<"("<<t.first<<","<<t.second<<")";}

#include <complex>
#include <cmath>
#define EPS 1.0e-10
#define INF 1.0e5
#define PI 3.1415926535897932384 

// 実数の符号関数
inline int signum(double x) { return (abs(x) < EPS ? 0 : x > 0 ? 1 : -1); }
//XY座標
#define X real()
#define Y imag()
// 点
typedef complex<double> P;
 

// 線分・半直線・直線
struct L { P pos, dir; L(P p=P(), P d=P()):pos(p),dir(d){}};

// 多角形
typedef vector<P> G;
 
// 円
struct C { P p; double r; };

// std::norm はabs(p)*abs(p)なので遅い
inline double norm(P p){
	return p.X*p.X+p.Y*p.Y;
}

// 二つのベクトルの内積を計算する
inline double inp(const P& a, const P& b) {
	return (conj(a)*b).real();
}
 
// 二つのベクトルの外積を計算する
inline double outp(const P& a, const P& b) {
	return (conj(a)*b).imag();
}

inline int ccw(const P& p, const P& r, const P& s) {
    P a(r-p), b(s-p);
    int sgn = signum(outp(a, b));
    if (sgn != 0)
        return sgn;
    if (a.real()*b.real() < -EPS || a.imag()*b.imag() < -EPS)
        return -1;
    if (norm(a) < norm(b) - EPS)
        return 1;
    return 0;
}

bool sp_intersects(const L& s, const P& p) {
    return ( abs(s.pos - p) + abs(s.pos + s.dir - p) - abs(s.dir) < EPS );
}
bool insideP(G& g, const P& p) {
	if(ccw(g[0], g[1], g[2]) != 1) swap(g[1], g[2]);
	if(norm(g[0]-p) < EPS || norm(g[1]-p) < EPS || norm(g[2]-p) < EPS) return false;
    double sum = 0.0;
    int n = g.size();
    if(n && g[0] == p) return false;
    for(int i = 0; i < n; i++) {
        int j = (i+1)%n;
        if (sp_intersects(L(g[i], g[j]-g[i]), p))
            return true;
        sum += arg((g[j]-p)/(g[i]-p));
    }
    return (abs(sum) > 1);
}

bool xy_less(const P& a, const P& b) {
    if (abs(a.imag()-b.imag()) < EPS) return (a.real() < b.real());
    return (a.imag() < b.imag());
}
template<class IN>
void walk_rightside(IN begin, IN end, vector<P>& v) {
    IN cur = begin;
    v.push_back(*cur++);
    vector<P>::size_type s = v.size();
    v.push_back(*cur++);
    while(cur != end) {
        if (v.size() == s || ccw(v[v.size()-2], v.back(), *cur) > EPS)
            v.push_back(*cur++);
        else
            v.pop_back();
    }
    v.pop_back();
}
//凸包を求める
vector<P> convex_hull(vector<P> v) {
    if (v.size() <= 1)
        return v; // EXCEPTIONAL
    sort(v.begin(), v.end(), xy_less);
    vector<P> cv;
    walk_rightside(v.begin(), v.end(), cv);
    walk_rightside(v.rbegin(), v.rend(), cv);
    return cv;
}

int n;
P S, T;

double dfs(P S1, P S2, vector<P> p, double l){
//	cout << "(" << S1 << ", " << S2  << ", " << l << ") start" << endl;
	G g, g2;
	g.push_back(S1);
	g.push_back(S2);
	g.push_back(T);
	g2.push_back(S1);
	g2.push_back(T);
	REP(i, p.size()) if(insideP(g, p[i])) g2.push_back(p[i]);
	g2 = convex_hull(g2);
	double sum = 0;
	if(g2.size() == 2 && abs(T-S1) < l+EPS){
//		cout << "3(" << S1 << ", " << S2  << ", " << l << ") = " << abs(S2-T) << endl << endl;
		return abs(S2-T);
	}
	REP(i, g2.size()) sum += abs(g2[i]-g2[(i+1)%g2.size()]);
	if(sum - abs(T-S1) < l+EPS){
//		cout << "2(" << S1 << ", " << S2  << ", " << l << ") = " << abs(S2-T) << endl << endl;
		return abs(S2-T);
	}
	double res = INF;
	REP(i, p.size()){
		if(norm(p[i]-S2) < EPS || !insideP(g, p[i])) continue;
//		cout << "!" << p[i] << endl;
		G g, g2;
		g.push_back(S1);
		g.push_back(S2);
		g.push_back(p[i]);
		g2.push_back(S1);
		g2.push_back(p[i]);
		REP(j, p.size()) if(i!=j && insideP(g, p[j])) g2.push_back(p[j]);
		g2 = convex_hull(g2);
//		cout << g2 << endl;
		double sum = 0;
		if(g2.size() == 2 && abs(p[i]-S1) < l+EPS) chmin(res, abs(S2-p[i]) + dfs(S1, p[i], p, l));
		REP(j, g2.size()) sum += abs(g2[j]-g2[(j+1)%g2.size()]);
		
		if(sum - abs(p[i]-S1) < l+EPS){
			P prev;
			REP(j, g2.size()) if(abs(g2[j]-p[i])<EPS) prev = g2[(j+g2.size()-1)%g2.size()];
//			cout << g2 << endl;
//			cout << "prev is " << prev << endl;
//			cout << "dfs" << prev << "," << p[i] << endl;
			chmin(res, abs(S2-p[i]) + dfs(prev, p[i], p, l-(sum - abs(p[i]-S1) - abs(p[i]-prev))));
		}
	}
//	cout << "1(" << S1 << ", " << S2 << ", " << l << ") = " << res << endl << endl;
	return res;
}

main(){
	while(cin >> n, n){
		vector<P> p;
		cin >> S.X >> S.Y >> T.X >> T.Y;
		REP(i, n){
			double x, y;
			cin >> x >> y;
			p.push_back(P(x, y));
		}
		if(ccw(P(0, 0), S, T) == -1){
			REP(i, n) p[i].Y = -p[i].Y;
			S.Y = -S.Y;
			T.Y = -T.Y;
		}
		double ret = dfs(P(0, 0), S, p, abs(S));
		if(ret > 90000) puts("-1");
		else printf("%.9f\n", ret);
	}
	return 0;
}
