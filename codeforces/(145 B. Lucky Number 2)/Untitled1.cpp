#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,a,b,c,d,p;
int main()
{
	cin>>a>>b>>c>>d;
	a-=c;
	b-=c;
	d-=c-1;
	if(d==1){
		if(a){ a--;p=1; }
        else { b--; p=2; }
	}
	if (d==2){
		a--; b--; p=3;
	}
	if(a<0||b<0||d<0||d>2){
		cout<<-1;
		return 0;
	}
	if (p&2) cout<<7;
	for (i=1;i<=a;i++) cout<<4;
	for (i=1;i<=c;i++) cout<<47;
	for (i=1;i<=b;i++) cout<<7;
	if(p&1) cout<<4;
	return 0;
}
