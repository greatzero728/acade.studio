#include <bits/stdc++.h>
using namespace std;

bool EuclideanFun(int n , long long * arr , long long p ,long long q,int ind)
{
    long long c = p/q;
    long long r = p%q;
    
    if(c != arr[ind])return false;
    
    if(ind==n-1)
    {
        if(r)return false;
        return true;
    }
    
    if(r==0)return false;
    
   return  EuclideanFun(n,arr,q,r,ind+1);
    
}

int main()
{
long long p,q;
cin>>p>>q;
    
int n;
cin>>n;
    
long long arr[n];
for(int i =0;i<n;i++)
    cin>>arr[i];
    
 if(n>1 && arr[n-1]==1)
    {
        arr[n-2]++;
        n--;
    }

bool ok = EuclideanFun(n,arr,p,q,0);
    ok?cout<<"YES\n":cout<<"NO\n";


}