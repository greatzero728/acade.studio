#include <bits/stdc++.h>
using namespace std;

const int N=4e5;
int n,arr[N+10];
bool match[N+10];
int cot[N*18],loc[N*18],roc[N*18],rot[N+10],x;
long long som[N*18],ans=0;

int find(int a){
    return arr[a]==a?a:arr[a]=find(arr[a]);
}
void update(int a,int l,int r,int &t){
    if(!t) t=++x;
    cot[t]++,som[t]+=a;
    if(l==r) return;
    int mid=(l+r)>>1;
    a<=mid?update(a,l,mid,loc[t]):update(a,mid+1,r,roc[t]);
}
void merge(int x,int &y){
    if(!x||!y) return y=x^y,void();
    ans+=som[loc[x]]*cot[roc[y]]-som[roc[y]]*cot[loc[x]];
    cot[y]+=cot[x],som[y]+=som[x];
    if(loc[x]||loc[y]) merge(loc[x],loc[y]);
    if(roc[x]||roc[y]) merge(roc[x],roc[y]);
}

int main(){
    cin>>n;
    iota(arr,arr+N,0);
    
    for(int i=1,a,b;i<=n;i++){
        cin>>a>>b;
        ans-=static_cast<long long>(a)*b,a=find(a),ans+=static_cast<long long>(a)*b,arr[a]=a+1,match[a]=1;
        update(b,1,n,rot[a]);
        if(match[a-1]) arr[a-1]=a,merge(rot[a-1],rot[a]);
        if(match[a+1]) merge(rot[a],rot[find(a+1)-1]);
        cout<<ans<<endl;
        
    }
}