#include <iostream>

using namespace std;

struct point {
    double x, y;
    point(double x = 0, double y = 0) : x(x), y(y) {}
    point operator - (point a) {return point(x - a.x, y - a.y);}
    double operator ^ (point a) {return x * a.y - y * a.x;}
} U[22], D[22];

int n;

struct line {
    point x, y;
    line(point x = point(0, 0), point y = point(0, 0)) : x(x), y(y) {}
} L;

bool is_located_strictly_above_the_line(point p) {
    return (L.x - p ^ L.y - p) > 0;
}

bool is_located_strictly_below_the_line(point p) {
    return (L.x - p ^ L.y - p) < 0;
}

double calc_the_left_most_interset_X_coordinate() {
    for(int i = 1; i <= n; i++) {
        if(is_located_strictly_above_the_line(D[i]) || is_located_strictly_below_the_line(U[i])) {
            
        }
    }
    return U[n].x;
}

void solve() {
    for(int i = 1; i <= n; i++) {
        cin>>U[i].x>>U[i].y;
        D[i] = point(U[i].x, U[i].y - 1);
    }
    double maxX = U[1].x;
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            L = line(U[i], U[j]), maxX = max(maxX, calc_the_left_most_interset_X_coordinate());
            L = line(U[i], D[j]), maxX = max(maxX, calc_the_left_most_interset_X_coordinate());
            L = line(D[i], U[j]), maxX = max(maxX, calc_the_left_most_interset_X_coordinate());
            L = line(D[i], D[j]), maxX = max(maxX, calc_the_left_most_interset_X_coordinate());
        }
    }
    if(maxX < U[n].x) printf("%.2lf\n", (double)maxX);
    else puts("Through all the pipe.");
}

int main() {
    while(scanf("%d", &n) && n) solve();
}