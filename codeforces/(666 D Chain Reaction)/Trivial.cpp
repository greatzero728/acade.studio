#include<bits/stdc++.h>
using namespace std;
const int Inf=2e9;
int ans_x[4],ans_y[4],sx,sy; vector<int> x,y;
int solve(){
	int ans=Inf;
	for(auto y1:y) for(auto y2:y){
		int d=abs(y1-y2);
		if(d==0) continue;
		set<int> se;
		for(auto x1:x) for(auto x2:x)
			for(auto d:{0,-d,-2*d,1,-d+1,-2*d+1})
				se.insert((x1+x2+d)/2);
		for(auto x1:se){
			int p[4]={0,1,2,3};
			for(int now=1;now<=24;now++){
				next_permutation(p,p+4);
				int sx[4]={x1,x1,x1+d,x1+d};
				int sy[4]={y1,y2,y1,y2};
				int flag=0;
				for(int i=0;i<4;i++)
					if(sx[i]!=x[p[i]]&&sy[i]!=y[p[i]]) flag=1;
				if(flag) continue;
				int t=0;
				for(int i=0;i<4;i++)
					t=max(t,abs(sx[i]-x[p[i]])+abs(sy[i]-y[p[i]]));
				if(ans<=t) continue; else ans=t;
				for(int i=0;i<4;i++) ans_x[p[i]]=sx[i],ans_y[p[i]]=sy[i];
			}
		}
	}
	return ans;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		x.clear(),y.clear();
		for(int i=1;i<=4;i++)
			scanf("%d%d",&sx,&sy),x.push_back(sx),y.push_back(sy);
		int t1=solve(); swap(x,y),swap(ans_x,ans_y);
		int t2=solve(); swap(x,y),swap(ans_x,ans_y);
		if(t1<t2) solve(); else t1=t2;//Choose the best solution
		if(min(t1,t2)==Inf) puts("-1"); else{
			printf("%d\n",t1);
			for(int i=0;i<4;i++) printf("%d %d\n",ans_x[i],ans_y[i]);
		}
	}
	return 0;
}