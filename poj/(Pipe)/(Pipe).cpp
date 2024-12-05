#include <iostream>

using namespace std;

struct point {
    double x, y;
    point(double x = 0, double y = 0) : x(x), y(y) {}
    point operator + (point a) {return point(x + a.x, y + a.y);}
    point operator - (point a) {return point(x - a.x, y - a.y);}
    point operator * (double a) {return point(x * a, y * a);}
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

double x_coordinate_of_interest_point(point ax, point ay, point bx, point by) {
    double sx = by - ax ^ ay - ax, sy = ay - ax ^ bx - ax, sum = sx + sy;
    point intersect_point = bx * (sx / sum) + by * (sy / sum);
    return intersect_point.x;
}

double calc_the_left_most_interset_X_coordinate() {
    for(int i = 1; i <= n; i++) {
        if(!is_located_strictly_below_the_line(U[i]) && !is_located_strictly_above_the_line(D[i])) continue;
        if(i == 1) return U[1].x;
        if(is_located_strictly_above_the_line(U[i - 1]) && is_located_strictly_below_the_line(U[i])) {
            return x_coordinate_of_interest_point(U[i - 1], U[i], L.x, L.y);
        }
        if(is_located_strictly_below_the_line(U[i - 1]) && is_located_strictly_above_the_line(U[i])) {
            return x_coordinate_of_interest_point(U[i - 1], U[i], L.x, L.y);
        }
        if(is_located_strictly_above_the_line(D[i - 1]) && is_located_strictly_below_the_line(D[i])) {
            return x_coordinate_of_interest_point(D[i - 1], D[i], L.x, L.y);
        }
        if(is_located_strictly_below_the_line(D[i - 1]) && is_located_strictly_above_the_line(D[i])) {
            return x_coordinate_of_interest_point(D[i - 1], D[i], L.x, L.y);
        }
        return U[i - 1].x;
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