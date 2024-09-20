#pragma comment(linker,"/stack:200000000")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include<stdio.h>
#include<set>
#define LL long long
#define re register
namespace IO{
	static char ibuf[1000010],*p1=ibuf,*p2=ibuf;
	inline char gc(){return p1==p2&&(p2=(p1=ibuf)+fread(ibuf,1,1000010,stdin),p1==p2)?EOF:*p1++;}
	inline void read(re LL &x){x=0;static char s=gc();while(s<'0'||s>'9')s=gc();while(s>='0'&&s<='9')x=(x<<3)+(x<<1)+(s^48),s=gc();}
	static char obuf[1000005];int len=-1;
	inline void flush(){fwrite(obuf,1,len+1,stdout);len=-1;}
	inline void pc(re const char x){if(len==1000000)flush();obuf[++len]=x;}
	inline void write(re LL x){static char o[20],p=0;while(x)o[++p]=x%10^48,x/=10;while(p)pc(o[p--]);}
}using namespace IO;
struct node{
	LL l,r;
	mutable bool v;
	node(LL x,LL y,bool z):l(x),r(y),v(z){}
	inline bool operator<(const node &x)const{
		return l<x.l;
	}
};
std::set<node>odt;
inline std::set<node>::iterator split(re const LL &x){
	re std::set<node>::iterator it=--odt.upper_bound(node(x,0,0));
	if(it->l==x)return it;
	re LL l=it->l,r=it->r;
	re bool v=it->v;
	odt.erase(it);
	odt.emplace(l,x-1,v);
	return odt.emplace(x,r,v).first;
}
LL q,op,l,r;
std::set<node>::iterator itl,itr;
int main(){
	odt.emplace(1,1000000000000000001,0);
	read(q);
	while(q--){
		read(op);read(l);read(r);
		itr=split(r+1),itl=split(l);
		switch(op){
			case 3:for(;itl!=itr;++itl)itl->v^=1;break;
			default:odt.erase(itl,itr);odt.emplace(l,r,op==1);
		}
		for(itl=odt.begin();itl!=odt.end();++itl){
			if(!itl->v){
				write(itl->l);pc('\n');break;
			}
		}
	}flush();
	return 0;
}