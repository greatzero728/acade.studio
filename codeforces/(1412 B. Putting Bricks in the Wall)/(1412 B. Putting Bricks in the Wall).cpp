#include <bits/stdc++.h>
using namespace std;

int main() {
   int t;
   cin >> t;
   while(t--){
       int n;
       cin>>n;
       char v[n][n];
       for(int i=0;i<n;i++){
           for(int j=0;j<n;j++)
               cin>>v[i][j];
       }
       char a1=v[0][1],a2=v[1][0],b1=v[n - 1][n - 2],b2=v[n - 2][n - 1];
       int c1 = 0 , c2 = 0;
        if(a1 == '0')
            c1++;
        else
            c2++;
        if(a2 == '0')
            c1++;
        else
            c2++;
       if(b1 == '1')
           c1++;
       else
           c2++;
       if(b2 == '1')
           c1++;
       else
           c2++;
       if(c1<=2){
           cout<<c1<<'\n';
           if(a1=='0')
               cout<<"1 2\n";
           if(a2=='0')
               cout<<"2 1\n";
           if(b1=='1')
               cout<<n<<' '<<n-1<<'\n';
           if(b2=='1')
               cout<<n-1<<' '<<n<<'\n';
       }else{
           cout<<c2<<'\n';
           if(a1=='1')
               cout<<"1 2\n";
           if(a2=='1')
               cout<<"2 1\n";
           if(b1=='0')
               cout<<n<<' '<<n-1<<'\n';
           if(b2=='0')
               cout<<n-1<<' '<<n<<'\n';
       }
   }
}