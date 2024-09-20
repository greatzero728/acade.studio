#include<bits/stdc++.h>
#define ri register LL
#define st set<nd>::iterator
using namespace std;
typedef long long LL;
inline LL rd(){
	LL x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return x*y;
}
struct nd{LL l,r;mutable LL v;bool operator<(const nd&o)const{return l<o.l;};};
LL n,m;set<nd>s;st p,q,x;
inline st sp(LL x){
	p=s.lower_bound((nd){x,0,0});if(p!=s.end()&&p->l==x)return p;
	--p;ri l=p->l,r=p->r,v=p->v;s.erase(p);s.insert((nd){l,x-1,v});return s.insert((nd){x,r,v}).first;
}
inline void add(LL l,LL r,LL v){q=sp(r+1);p=sp(l);s.erase(p,q);s.insert((nd){l,r,v});}
int main(){
	n=rd();s.insert((nd){1,2000000000000000000ll,0});
	for(ri op,l,r;n--;){
		op=rd();l=rd();r=rd();
		if(op==3){q=sp(r+1);p=sp(l);for(x=p;x!=q;++x)x->v=!x->v;}else add(l,r,op&1);
		for(x=s.begin();x!=s.end();++x)if(!x->v){printf("%lld\n",x->l);break;}
	}
	return 0;
}