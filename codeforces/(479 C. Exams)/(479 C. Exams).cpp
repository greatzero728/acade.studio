#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int main() {
    int n;
    cin >> n;

    vector<pii> exams(n);
    for (int i = 0; i < n; i++) {
        cin >> exams[i].first >> exams[i].second;
    }

    sort(exams.begin(), exams.end());

    int current_date = 0;
    int max_scheduled_date = 0;

    for (int i = 0; i < n; i++) {
        max_scheduled_date = max(max_scheduled_date, exams[i].first);
        if (exams[i].second >= current_date) {
            current_date = exams[i].second;
        } else {
            current_date = max_scheduled_date;
        }
    }

    cout << current_date << endl;

    return 0;
}