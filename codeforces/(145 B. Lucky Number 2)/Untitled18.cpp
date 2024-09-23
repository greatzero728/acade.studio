#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#define size 2000005
using namespace std;
int a,b,c,d,p;

int main()
{
	cin>>a>>b>>c>>d;
	d-=c-1;
	a-=c;
	b-=c;
	if (d==2){a--;b--;p=3;}
	if (d==1){if(a) {a--;p=1;}else{b--;p=2;}}
	if (a<0||b<0||d>2||d<0)
		cout<<"-1"; else 
		{
			if (p&2) cout<<"7";
			for (;a>0;a--) cout<<"4";
			for (;c>0;c--) cout<<"47";
			for (;b>0;b--) cout<<"7";
			if (p&1) cout<<"4";
			}
	return 0;
		}
	
	
	