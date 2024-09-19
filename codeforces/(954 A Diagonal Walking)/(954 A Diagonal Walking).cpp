#include <bits/stdc++.h>
using namespace std;
    typedef long long ll;
int main()
{
  int n;cin>>n;string s;cin>>s;
  bool flag[n]={};
  int cnt=0;
  for(int i=1;i<n;i++)
  {
      if((s[i]=='R'&&s[i-1]=='U')||(s[i]=='U'&&s[i-1]=='R'))
      {
          if(flag[i]==flag[i-1]&&flag[i]==0)
          {
              cnt++;
              flag[i]=1;
          }
      }
  }
  cout<<n-cnt;
}