#include <bits/stdc++.h>
using namespace std;
vector<int> showcase;
int result[200001];
int main() 
{
    int n, shurikenIndex=0;
    char eventType;
    cin >> n;
    for (int i = 0; i < 2 * n; i++) 
    {
        cin >> eventType;
        int price;
        if (eventType == '-') 
        {
            if (showcase.empty()) {
                cout << "NO";
                return 0;
            }
            cin >> price;
            int lastShurikenIndex = showcase.back();
            showcase.pop_back();
            if (price < result[lastShurikenIndex + 1]) {
                cout << "NO";
                return 0;
            }
            result[lastShurikenIndex] = price;
        }
        else {
            showcase.push_back(shurikenIndex);
            shurikenIndex++;
        }
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        cout << result[i] << " ";
    }
}