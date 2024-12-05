#include <cassert>// c
#include <ctime>
#include <iostream>// io
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>// container
#include <map>
#include <set>
#include <queue>
#include <bitset>
#include <stack>
#include <algorithm>// other
#include <complex>
#include <numeric>
#include <functional>
#include <random>
#include <regex>

using namespace std;
typedef long long ll;

#define ALL(c) (c).begin(),(c).end()
#define FOR(i,l,r) for(int i=(int)l;i<(int)r;++i)
#define REP(i,n) FOR(i,0,n)
#define FORr(i,l,r) for(int i=(int)r-1;i>=(int)l;--i)
#define REPr(i,n) FORr(i,0,n)
#define EACH(i,c) for(__typeof((c).begin()) i=(c).begin(); i!=(c).end(); ++i)
#define IN(l,v,r) ((l)<=(v) && (v)<(r))
#define UNIQUE(v) v.erase(unique(ALL(v)),v.end())
//debug
#define DUMP(x)  cerr << #x << " = " << (x)
#define LINE()    cerr<< " (L" << __LINE__ << ")"

template<typename T,typename U> T pmod(T x,U M){return (x%M+M)%M;}


// must template
typedef long double D;
const D INF = 1e12,EPS = 1e-8;

typedef complex<D> P;
#define X real()
#define Y imag()
istream& operator >> (istream& is,complex<D>& p){D x,y;is >> x >> y;p=P(x,y);return is;}

int sig(D a,D b=0){return a<b-EPS?-1:a>b+EPS?1:0;}
template<typename T> bool eq(const T& a,const T& b){return sig(abs(a-b))==0;}
bool compX (const P& a,const P& b){return !eq(a.X,b.X)?sig(a.X,b.X)<0:sig(a.Y,b.Y)<0;}


// a×b
D cross(const P& a,const P& b){return imag(conj(a)*b);}
// a・b
D dot(const P& a,const P& b) {return real(conj(a)*b);}
int ccw(const P& a,P b,P c){
    b -= a; c -= a;
    if (cross(b,c) > EPS)   return +1;       // counter clockwise
    if (cross(b,c) < -EPS)   return -1;       // clockwise
    if (dot(b,c) < 0)     return +2;       // c--a--b on line
    if (norm(b) < norm(c)) return -2;       // a--b--c on line
    return 0; //a--c--b on line (c==b,c==a)
}
const P O=P(0,0);
P s,g;
bool Comp(const P& p1,const P&p2){
	if(abs(ccw(O,p1,p2))!=1)return abs(p1)>abs(p2);//sameline
	return ccw(O,p1,p2)==ccw(O,s,g);
}
namespace std{
	bool operator <  (const P& a,const P& b){return Comp(a,b);}
  	bool operator == (const P& a,const P& b){return eq(a,b);}
};
// //must template

//浮動小数点 pmod
D pfmod(D v,D M=2*M_PI){return fmod(fmod(v,M)+M,M);}

//[0,PI)
D AbsArg(D a){
	D ret=pfmod(max(a,-a),2);return min(ret,2*M_PI-ret);
}

int n;
vector<P> useps;

vector<bool> willpass;
typedef vector<P> Poly,ConvexPoly;

enum { OUT, ON, IN };
int contains(const Poly& ps, const P& p) {
	bool in = false;
	REP(i,ps.size()){
		P a = ps[i] - p, b = ps[pmod(i+1,ps.size())] - p;
		if(a.Y > b.Y) swap(a, b);
		if(a.Y <= 0 && 0 < b.Y)if (cross(a, b) < 0) in = !in;
    	if(cross(a, b) == 0 && dot(a, b) <= 0) return ON;
  	}
	return in ? IN : OUT;
}

bool passcheck(const P& pos,const P& o,const P&to){
	REP(j,willpass.size())if(willpass[j])if(contains({o,pos,to},useps[j])!=OUT)return false;
	return true;
}

bool canover(const P& pos,const P& o,const P&to){
	REP(j,willpass.size())if(willpass[j])if(contains({o,pos,to},useps[j])==IN)return false;
	return true;
}

D dfs(int i,const P& pos,const P& o,D len){
	if(useps[i]==g){
		if(passcheck(pos,o,useps[i]) && sig(abs(g-o),len)<=0) return abs(g-pos);
		else return INF;
	}
	D d=INF;//search
	if(contains({o,pos,g},useps[i])){//引っかかる場合
		//迂回なし
		if(canover(pos,o,useps[i]))
			d=min(d,dfs(i+1,pos,useps[i],len-abs(useps[i]-o)));//迂回させない
		//迂回させる
	    if(passcheck(pos,o,useps[i])){
	    	vector<bool> tmp=willpass;
	    	fill(ALL(willpass),false);
	        d=min(d,abs(useps[i]-pos)+dfs(i+1,useps[i],o,len));//迂回して通す
	    	willpass=tmp;
	    }
		//そのうち迂回させて通す
		willpass[i]=true;
		d=min(d,dfs(i+1,pos,o,len));//迂回して通す
	    willpass[i]=false;
	}else{//引っかからない場合
     	d=min(d,dfs(i+1,pos,o,len));//迂回なし	
	}
	return d;
}

int main(){
	cout <<fixed <<setprecision(20);
	cerr <<fixed <<setprecision(20);

	while(true){
		cin >> n;if(n==0)break;
		useps.clear();

		cin >> s >> g;
		vector<P> ps(n);REP(i,n)cin >> ps[i];
		
		// only contained
		REP(i,n) if(contains({O,s,g},ps[i])) useps.push_back(ps[i]);
		useps.push_back(g);
		sort(ALL(useps),Comp);

		willpass=vector<bool>(useps.size());

		//始点
		D res=dfs(0,s,O,abs(s));
		if(sig(res,INF)<0) cout << res <<endl;
		else cout << -1 <<endl;
	}
	return 0;
 }
