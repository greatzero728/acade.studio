#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        string str;
        cin >> str;
        string str1 = "";
        str1 += str[0];
        for (int i = 1; i < str.size(); i++)
        {
            if (str[i] == str[i - 1])
                continue;
            else
            {
                str1 += str[i];
            }
        }
        bool flag = true;
        for (int i = 0; i < str1.size() / 2; i++)
        {
            if (str1[i] != str1[str1.size() - 1 - i])
            {
                flag = false;
                break;
            }
        }
        if (flag)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}