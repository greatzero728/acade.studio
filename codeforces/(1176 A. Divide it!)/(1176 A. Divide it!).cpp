#include <bits/stdc++.h>
using namespace std;

int main() {
   int q;
   cin >> q;
   while(q--){
       unsigned long long n;
       cin >> n;
       int count = 0 ;
       bool can = true;
       while(n != 1){
           while (n % 2 == 0 && n != 1)
               count++, n /= 2;
           while (n % 5 == 0 && n != 1)
               n = (4 * n) / 5, count++;
           while (n % 3 == 0 && n != 1)
               n = (2 * n) / 3, count++;
           if (n % 2 != 0 && n % 3 != 0 && n % 5 != 0 && n != 1)
               can = false;
           if (!can)
               break;
       }
       if(can)
           cout << count << endl;
       else
           cout << -1 << endl;
   }
}