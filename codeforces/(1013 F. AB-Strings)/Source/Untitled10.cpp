// LUOGU_RID: 96121061
#include<bits/stdc++.h>
using namespace std;
constexpr int N=200000;
char ch1[N+10],ch2[N+10];
deque<int> q1,q2;
int st1,st2,p;
struct oper{
	int u,v,p;
};
vector<oper> vec;
void solve(){
	if(q1.size()<q2.size()) swap(q1,q2),swap(st1,st2),p^=1;
	if(st1==st2){
		if(q2.size()==1){
			if(q1.size()>3){
				int a1=q1[0],a2=q1[1],a3=q1[2];
				q1.pop_front(),q1.pop_front(),q1.pop_front();
				vec.push_back({a1+a2+a3,0,p});
				q2.front()+=a3;
				q2.push_front(a2);
				q2.push_front(a1);
				st1^=1;
				return;
			}
		}
		if(q1.size()>=3){
			int a1=q1[0],a2=q1[1],b1=q2[0];
			vec.push_back({a1+a2,b1,p});
			q1.pop_front(),q1.pop_front(),q2.pop_front();
			q1.front()+=b1;
			if(q2.empty()) q2.push_front(a2);
			else q2.front()+=a2;
			q2.push_front(a1);
		}
		else{
			int tmp=q1.front();
			q1.pop_front();
			vec.push_back({tmp,0,p});
			st1^=1;
			q2.front()+=tmp;
		}
	}
	else{
		if(q1.size()>=q2.size()+3&&q2.size()){
			int a1=q1[0],a2=q1[1],a3=q1[2];
			q1.pop_front(),q1.pop_front(),q1.pop_front();
			int b1=q2[0];
			vec.push_back({a1+a2+a3,b1,p});
			q2.pop_front();
			q1[0]+=b1;
			if(q2.empty()) q2.push_front(a3);
			else q2.front()+=a3;
			q2.push_front(a2),q2.push_front(a1);
		}
		else{
			int a1=q1[0],b1=q2[0];
			vec.push_back({a1,b1,p});
			q1.pop_front(),q2.pop_front();
			if(q1.empty()) q1.push_back(b1);
			else q1.front()+=b1;
			if(q2.empty()) q2.push_back(a1);
			else q2.front()+=a1;
		}
		swap(st1,st2);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>ch1+1>>ch2+1;
	st1=ch1[1]-'a';
	st2=ch2[1]-'a';
	int i,n;
	n=strlen(ch1+1);
	for(i=1;i<=n;++i){
		if(ch1[i]!=ch1[i-1]) q1.push_back(1);
		else ++q1.back();
	}
	n=strlen(ch2+1);
	for(i=1;i<=n;++i){
		if(ch2[i]!=ch2[i-1]) q2.push_back(1);
		else ++q2.back();
	}
	while(q1.size()>1||q2.size()>1){
		solve();
	}
	cout<<vec.size()<<'\n';
	for(auto &i:vec){
		if(i.p) swap(i.u,i.v);
		cout<<i.u<<' '<<i.v<<'\n';
	}
	return 0;
}
