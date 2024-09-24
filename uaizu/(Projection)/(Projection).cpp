#include <bits/stdc++.h>

using namespace std;

struct Point {
    double x, y;
};

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

int main() {
    Point p1, p2;
    int q;
    cin >> p1.x >> p1.y >> p2.x >> p2.y >> q;
    Point a = {p2.x - p1.x, p2.y - p1.y};
    while (q--) {
        Point p;
        cin >> p.x >> p.y;
        Point b = {p.x - p1.x, p.y - p1.y};
        double k = dot(b, a) / dot(a, a);
        Point res = {p1.x + a.x * k, p1.y + a.y * k};
        cout << fixed << setprecision(10) << res.x << " " << res.y << "\n";
    }
    return 0;
}