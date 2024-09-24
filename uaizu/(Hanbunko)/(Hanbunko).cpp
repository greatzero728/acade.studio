#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;
};

long long cross(Point& a, Point& b) {
    return 1ll * a.x * b.y - 1ll * a.y * b.x;
}

long long get_area(vector<Point>& v) {
    long long res = 0;
    for (int i = 0; i < v.size(); i++) {
        res += cross(v[i], v[(i + 1) % v.size()]);
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    vector<Point> c(n);
    for (auto& ci: c) cin >> ci.x >> ci.y;
    long long area = get_area(c), tmp_area = 0;
    int j = 1;
    long long ans = 1e18;
    for (int i = 0; i < n; i++) {
        while (area > 2 * tmp_area) {
            j = (j + 1) % n;
            vector<Point> tmp = {c[i], c[(j - 1 + n) % n], c[j]};
            tmp_area += get_area(tmp);
            ans = min(ans, abs(area - tmp_area * 2));
        }
        vector<Point> tmp = {c[i], c[(i + 1) % n], c[j]};
        tmp_area -= get_area(tmp);
        ans = min(ans, abs(area - tmp_area * 2));
    }
    cout << fixed << ans / 2.0 << "\n";
    return 0;
}