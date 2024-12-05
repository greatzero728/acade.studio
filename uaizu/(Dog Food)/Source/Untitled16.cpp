#include <iostream>
#include <cmath>
#include <vector>
#include <complex>
#include <cassert>
#include <algorithm>
using namespace std;

typedef complex<double> point;

struct line : public vector<point> {
	line(const point& a, const point& b) { push_back(a); push_back(b); }
};

const double pi  = M_PI;
const double inf = 1e10;
const double eps = 1e-10;
point  unit (const point& v)                 { return v/abs(v);     }
point  ortho(const point& v)                 { return v*point(0,1); }
point  vec  (const line&  l)                 { return l[1]-l[0];    }
bool   equal(const double a, const double b) { return abs(a-b)<eps; }
bool   equal(const point& a, const point& b) { return abs(a-b)<eps; }
double dot  (const point& a, const point& b) { return (a*conj(b)).real(); }
double cross(const point& a, const point& b) { return (conj(a)*b).imag(); }

int ccw(const point& a, const point& b, const point& c) {
	point u=b-a, v=c-a;
	if(cross(u,v) > 0 ) return +1; // ccw
	if(cross(u,v) < 0 ) return -1; // cw
	if(  dot(u,v) < 0 ) return +2; // cab
	if(abs(u) < abs(v)) return -2; // abc
	return 0;                      // acb
}

int ccw(const line& s, const point& p) {
	return ccw(s[0], s[1], p);
}

point crosspoint(const line& l, const line& m) {
	double A = cross(vec(l), vec(m));
	double B = cross(vec(l), l[1]-m[0]);
	if(abs(A)<eps) {			// parallel
		assert(abs(B)<eps);
		return m[1];			// sameline
	}
	return m[0] + B/A*vec(m);
}

bool contain(const point& a, const point& b, const point& c, const point& p) {
	return (ccw(a,b,p)!=-1 && ccw(b,c,p)!=-1 && ccw(c,a,p)!=-1)
	    || (ccw(a,b,p)!=+1 && ccw(b,c,p)!=+1 && ccw(c,a,p)!=+1);
}

int N;
point pile[8],dog,food;

pair<double,point> check(point base, point curr, point dest, double rest) {
	//cout << base << curr << dest << rest << endl;
	int mi=-1;
	double md=0,ma=inf;
	for(int i=0; i<N; i++) {
		if(equal(pile[i],base)) continue;
		if(equal(pile[i],curr)) continue;
		if(equal(pile[i],dest)) continue;
		if(equal(base,curr)) continue;
		if(equal(curr,dest)) continue;
		if(equal(dest,base)) continue;
		if(!contain(base,curr,dest,pile[i])) continue;
		double d = abs(pile[i]-base);
		double a = abs(arg(curr-base)-arg(pile[i]-base));
		if(equal(a,ma)) {
			if(md<d) { mi=i; md=d; ma=a; }
		}
		else if(a<ma) {
			mi=i; md=d; ma=a;
		}
	}

	if(mi<0) return make_pair(rest,base);

	line l(base, pile[mi]);
	line m(curr, dest);
	curr = crosspoint(l,m);
	return check(pile[mi], curr, dest, rest-abs(pile[mi]-base));;
}

double solve(int use, point base, point curr, double rest, double dist) {
	pair<double,point> ret = check(base,curr,food,rest);
	if(ret.first >= abs(ret.second-food)) return dist + abs(food-curr);
	double ans=inf;
	for(int i=0; i<N; i++) {
		if(use&(1<<i)) continue;
		ret = check(base,curr,pile[i],rest);
		if(ret.first < 0) continue;
		ans=min(ans,solve(use|(1<<i), ret.second, pile[i], ret.first, dist+abs(pile[i]-curr)));
	}
	return ans;
}

int main()
{
	while(cin>>N, N)
	{
		cin >> dog.real() >> dog.imag();
		cin >> food.real() >> food.imag();
		for(int i=0; i<N; i++) {
			cin >> pile[i].real() >> pile[i].imag();
		}
		cout.setf(ios::fixed); cout.precision(10);
		double ans = solve(0, 0, dog, abs(dog), 0);
		if(ans==inf) cout << "-1" << endl;
		else cout << ans << endl;
	}		
}
