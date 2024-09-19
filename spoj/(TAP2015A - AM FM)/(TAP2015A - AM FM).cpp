#include <bits/stdc++.h>

using namespace std;
using DO = long double;

const DO eps = 1e-9;
const int NN = 1212;

struct point {
	DO x, y;
	point(DO x = 0, DO y = 0) : x(x), y(y) {}
	point operator + (point a) {return point(x + a.x, y + a.y);}
	point operator - (point a) {return point(x - a.x, y - a.y);}
	point operator * (DO s) {return point(x * s, y * s);}
	DO operator * (point a) {return x * a.x + y * a.y;}
	point operator & (point a) {
		return point(x * a.x - y * a.y, x * a.y + y * a.x);
	}
	point rotate (DO al) {return *this & point(cosl(al), sinl(al));}
	DO nor() {return sqrtl(*this * *this);}
	DO nor2() {return *this * *this;}
	point norm() {
		DO s = nor();
		return s < eps ? *this : point(x / s, y / s);
	}
} p[NN];

int X[NN], Y[NN], R[NN];

int main() {
	int n; cin>>n;
	vector<point> vec;
	for(int i = n; i--; ) {
		cin>>X[i]>>Y[i]>>R[i];
		vec.push_back(point(X[i], Y[i]));
	}
	
	for(int i = n; i--; ) {
		point p1 = point(X[i], Y[i]); DO r1 = R[i];
		for(int j = i; j--; ) {
			point p2 = point(X[j], Y[j]); DO r2 = R[j];
			
			DO d = (p1 - p2).nor();
			if(d > r1 + r2 + eps || d < fabsl(r1 - r2) - eps) continue;
			
			DO al = acosl((r1 * r1 + d * d - r2 * r2) / (2 * r1 * d));
			
			vec.push_back(p1 + (p2 - p1).rotate(al).norm() * r1);
			vec.push_back(p1 + (p2 - p1).rotate(-al).norm() * r1);
		}
	}
	
	int ans = 1;
	for(point P: vec) {
		int num = 0;
		for(int i = n; i--; ) {
			if((point(X[i], Y[i]) - P).nor2() < R[i] * R[i] + eps) num++;
		}
		ans = max(ans, num);
	}
	cout<<ans<<endl;
	return 0;
}