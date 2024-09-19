//#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
signed main() {
    int n, rating;
    cin >> n >> rating;
    vector<pair<int, int>> positive, negative;
    for (int i = 1; i <= n ; ++i) {
        int a, b;
        cin >> a >> b;
        if (b >= 0) positive.push_back({a, b});
        else negative.push_back({a, b});
    }
    sort(positive.begin(), positive.end());
    for (auto [min_rating, cost] : positive) {
        if (rating < min_rating) {
            cout << "NO\n";
            return 0;
        }
        rating += cost;
    }
    for (int i = 0; i < negative.size(); ++i) {
        negative[i].first = max(negative[i].first, -negative[i].second);
    }
    sort(negative.begin(), negative.end(), [&](pair<int, int> a, pair<int, int> b){
         return a.first + a.second > b.first + b.second;
    });
    for (auto [min_rating, cost] : negative) {
        if (rating < min_rating) {
            cout << "NO\n";
            return 0;
        }
        rating += cost;
    }
    cout << "YES\n";
    return 0;
}
