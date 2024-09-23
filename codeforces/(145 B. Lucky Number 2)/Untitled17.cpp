#include <bits/stdc++.h>
#pragma O3
using namespace std;
int main(){
    int a,b,c,d,p;
    cin>>a>>b>>c>>d;
	a-=c;b-=c;d-=c-1; p=0;
	if(d==2) a--,b--,p=3;
	if(d==1){
		if(a) a--,p=1;
		else b--,p=2;
	}
	if(a<0||b<0||d>2||d<0){
		cout<<-1;
		return 0;
	}
	if(p&2) cout<<7;
	for(int i=0;i<a;i++) cout<<4;
	for(int i=0;i<c;i++) cout<<47;
	for(int i=0;i<b;i++) cout<<7;
	if(p&1) cout<<4;
}
   	 		 	 	 	        			   		 	