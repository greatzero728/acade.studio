#include <iostream>
#include <iomanip>
#include <complex>
#include <vector>
#include <algorithm>
#include <cmath>
#include <array>
using namespace std;

const double EPS = 1e-10;
const double INF = 1e12;
const double PI = acos(-1);
#define EQ(n,m) (abs((n)-(m)) < EPS)
#define X real()
#define Y imag()

typedef complex<double> P;
typedef vector<P> VP;
struct L : array<P, 2>{
    L(const P& a, const P& b){ at(0)=a; at(1)=b; }
    L(){}
};

namespace std{
    bool operator < (const P& a, const P& b){
        return !EQ(a.X,b.X) ? a.X<b.X : a.Y<b.Y;
    }
    bool operator == (const P& a, const P& b){
        return abs(a-b) < EPS;
    }
}

double dot(P a, P b){
    return (conj(a)*b).X;
}
double cross(P a, P b){
    return (conj(a)*b).Y;
}
int ccw(P a, P b, P c){
    b -= a;
    c -= a;
    if(cross(b,c) > EPS) return +1; //ccw
    if(cross(b,c) < -EPS) return -1; //cw
    if(dot(b,c) < -EPS) return +2; //c-a-b
    if(abs(c)-abs(b) > EPS) return -2; //a-b-c
    return 0; //a-c-b
}

bool intersectSP(const L& s, const P &p){
    return abs(cross(s[0]-p, s[1]-p))<EPS  && dot(s[0]-p, s[1]-p)<EPS;
}

int in_poly(const P &p, const VP &poly){
    int n = poly.size();
    int ret = -1;
    for(int i=0; i<n; i++){
        P a = poly[i]-p;
        P b = poly[(i+1)%n]-p;
        if(a.Y > b.Y) swap(a,b);
        if(intersectSP(L(a,b), P(0,0))) return 0;
        if(a.Y<=0 && b.Y>0 && cross(a,b)<0) ret = -ret;
    }
    return ret;
}

VP convex(VP v){
    VP ret;
    int n = v.size();
    sort(v.begin(), v.end());
    for(int i=0; i<n; i++){
        while((int)ret.size()>1 && cross(ret.back()-ret[ret.size()-2], v[i]-ret.back()) < EPS){
            ret.pop_back();
        }
        ret.push_back(v[i]);
    }
    int t = ret.size();
    for(int i=n-2; i>=0; i--){
        while((int)ret.size()>t && cross(ret.back()-ret[ret.size()-2], v[i]-ret.back()) < EPS){
            ret.pop_back();
        }
        ret.push_back(v[i]);
    }
    if((int)ret.size() > 1) ret.pop_back();
    return ret;
}

vector<bool> used(10, false);
double limit;
double solve(P pos, P goal, P pivot, double len, VP &pin){
	if(len + abs(pos-pivot) > limit +EPS) return INF;
	if(pos == goal) return 0;
	
	int n = pin.size()-2;
	double dist = INF;
	for(int i=0; i<n+2; i++){
		if(used[i]) continue;
		used[i] = true;
		
		P newpivot = pivot;
		double newlen = len;
		
		VP tri{pos, pin[i], pivot};
		if(ccw(tri[0], tri[1], tri[2]) == -1) swap(tri[1], tri[2]);
		VP plist{pivot, pin[i]};
		for(int j=0; j<n+1; j++){
			if(in_poly(pin[j], tri) == 1){
				plist.push_back(pin[j]);
			}
		}
		sort(plist.begin(), plist.end());
		plist.erase(unique(plist.begin(), plist.end()), plist.end());
		
		if((int)plist.size() >= 3){
			VP cvx = convex(plist);
			for(int j=0; j<(int)cvx.size(); j++){
				if(cvx[j] == pivot){
					cvx.insert(cvx.end(), cvx.begin(), cvx.begin()+j);
					cvx.erase(cvx.begin(), cvx.begin()+j);
					break;
				}
			}
			if(cvx[1] == pin[i]) reverse(cvx.begin()+1, cvx.end());
			for(int j=0; j<(int)cvx.size()-2; j++){
				newlen += abs(cvx[j+1] -cvx[j]);
			}
			newpivot = *(cvx.end() -2);
		}
		
		P online(INF, INF);
		for(int j=0; j<=n; j++){
			if(intersectSP(L(newpivot, pin[i]), pin[j]) && pin[j]!=newpivot && i!=j){
				if(abs(pin[i] -online) > abs(pin[i] -pin[j])){
					online = pin[j];
				}
			}
		}
		if(online!=P(INF, INF)){
			newlen += abs(newpivot -online);
			newpivot = online;
		}
		dist = min(dist, solve(pin[i], goal, newpivot, newlen, pin) +abs(pos-pin[i]));
		
		used[i] = false;
	}
	return dist;
}

int main(){
	cout << fixed;
	cout << setprecision(10);
	
	while(1){
		int n;
		cin >> n;
		if(n==0) break;
		
		double x,y;
		P s,g;
		cin >> x >> y;  s = P(x, y);
		cin >> x >> y;  g = P(x, y);
		
		VP pin(n+2); //0:????, 1~n:?, n+1:???
		pin[0] = P(0, 0);
		for(int i=1; i<=n; i++){
			cin >> x >> y;
			pin[i] = P(x, y);
		}
		pin[n+1] = g;
		limit = abs(s);
		
		if(abs(g) > abs(s) +EPS){
			cout << -1 << endl;
		}else{
			double ans = solve(s, g, pin[0], 0, pin);
			cout << ans << endl;
		}
	}
    return 0;
}
