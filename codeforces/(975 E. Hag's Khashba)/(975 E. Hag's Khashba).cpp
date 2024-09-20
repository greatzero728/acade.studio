#include<bits/stdc++.h>

using namespace std;

using DO = double;

const DO eps = 1e-7;

struct point {
	DO x, y;
	point(DO x = 0, DO y = 0) : x(x), y(y) {}
	point operator + (point a) {return point(x + a.x, y + a.y);}
	point operator - (point a) {return point(x - a.x, y - a.y);}
	point operator * (DO a) {return point(x * a, y * a);}
	point operator / (DO a) {return point(x / a, y / a);}
	DO operator ^ (point a) {return x * a.y - y * a.x;}
	DO operator * (point a) {return x * a.x + y * a.y;}
	point operator & (point a) {
		return point(x * a.x - y * a.y, x * a.y + y * a.x);
	}
	point rotate (DO Cos, DO Sin) {return *this & point(Cos, Sin);}
	DO nor() {return sqrt(*this * *this);}
	point norm() {
		DO s = nor();
		return s < eps ? *this : point(x / s, y / s);
	}
	void input() {scanf("%lf %lf", &x, &y);}
	void print() {printf("%lf %lf\n", x, y);}
};

const int NN = 10101;

point p[NN], dir[NN], C;
DO d[NN];

point get(int f, int u) {
    DO Cos = dir[f] * dir[u] / (d[f] * d[u]);
    DO Sin = dir[f] ^ dir[u] / d[f] / d[u];
    return C + (p[f] - C).norm().rotate(Cos, Sin) * d[u];
}

int main() {
    int n, q; scanf("%d %d", &n, &q);
    for(int i = 1; i <= n; i++) p[i].input();
    
    DO area = 0;
    for(int i = 2; i < n; i++) {
        DO triangle_area_x_2 = p[i] - p[1] ^ p[i + 1] - p[1];
        C = C + (p[1] + p[i] + p[i + 1]) / 3 * triangle_area_x_2;
        area += triangle_area_x_2;
    }
    C = C / area;
    
    for(int i = 1; i <= n; i++) {
        dir[i] = p[i] - C;
        d[i] = dir[i].nor();
    }
    
    int a = 1, b = 2;
    while(q--) {
        int tp; scanf("%d", &tp);
        if(tp == 1) {
            int f, t; scanf("%d %d", &f, &t);
            if(a == f) swap(a, b);
            
            C = p[a], C.y -= d[a];
            p[t] = get(a, t);
            b = t;
        }
        else {
            int v; scanf("%d", &v);
            p[v] = get(a, v);
            p[v].print();
        }
    }
}