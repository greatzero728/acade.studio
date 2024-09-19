#include <bits/stdc++.h>
using namespace std;
int main() 
{
    int n, m;
    cin >> n >> m;
    if (m == 3 && n >= 5)
    {
        cout << -1;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            int x = i;
            int y = 10000000 + i * i;
            if (i >= m)
                y *= -1;
            cout << x << " " << y << endl;
        }
    }
    return 0;
}