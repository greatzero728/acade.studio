#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;
};

bool isInsideCircle(Point p, Point c, int r) {
    return (p.x - c.x) * (p.x - c.x) + (p.y - c.y) * (p.y - c.y) <= r * r;
}

bool isInsideSquare(Point p, Point s, int l) {
    return s.x <= p.x && p.x <= s.x + l && s.y <= p.y && p.y <= s.y + l;
}

double triangleArea(Point p1, Point p2, Point p3) {
    return abs(0.5 * (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)));
}

bool isInsideTriangle(Point p, Point t1, Point t2, Point t3) {
    double area = triangleArea(t1, t2, t3);
    return abs(area - (triangleArea(p, t1, t2) + triangleArea(p, t2, t3) + triangleArea(p, t3, t1))) < 1e-9;
}

int main() {
    int T; scanf("%d", &T);
    while(T--) {
        int N; scanf("%d", &N);
        set<pair<int, int>> points;
        while(N--) {
            char tp; scanf(" %c", &tp);
            if(tp == 'T') {
                int x1, y1, x2, y2, x3, y3; scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
                for(int i = -50; i <= 100; i++) {
                    for(int j = -50; j <= 100; j++) {
                        if(isInsideTriangle({i, j}, {x1, y1}, {x2, y2}, {x3, y3})) {
                            points.insert({i, j});
                        }
                    }
                }
            }
            else if(tp == 'C') {
                int x, y, r; scanf("%d %d %d", &x, &y, &r);
                for(int i = -50; i <= 100; i++) {
                    for(int j = -50; j <= 100; j++) {
                        if(isInsideCircle({i, j}, {x, y}, r)) {
                            points.insert({i, j});
                        }
                    }
                }
            }
            else {
                int x, y, l; scanf("%d %d %d", &x, &y, &l);
                for(int i = -50; i <= 100; i++) {
                    for(int j = -50; j <= 100; j++) {
                        if(isInsideSquare({i, j}, {x, y}, l)) {
                            points.insert({i, j});
                        }
                    }
                }
            }
        }
        printf("%d\n", points.size());
    }
}