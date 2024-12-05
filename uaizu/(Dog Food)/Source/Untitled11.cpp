#include<cmath>
#include<cstdio>
#include<algorithm>

#define rep(i,n) for(int i=0;i<(n);i++)

using namespace std;

const double EPS=1e-7;
const double INF=1e77;
const double PI=acos(-1);

template<class T>
struct point{
	T x,y;
	point &operator+=(const point &a){ x+=a.x; y+=a.y; }
	point &operator-=(const point &a){ x-=a.x; y-=a.y; }
	point operator+(const point &a)const{ return (point){x+a.x,y+a.y}; }
	point operator-(const point &a)const{ return (point){x-a.x,y-a.y}; }
};

template<class T>
point<T> operator*(T c,const point<T> &a){ return (point<T>){c*a.x,c*a.y}; }

bool operator==(const point<double> &a,const point<double> &b){
	return abs(a.x-b.x)<EPS && abs(a.y-b.y)<EPS;
}
bool operator!=(const point<double> &a,const point<double> &b){
	return abs(a.x-b.x)>EPS || abs(a.y-b.y)>EPS;
}

template<class T>
T cross(const point<T> &a,const point<T> &b){ return a.x*b.y-a.y*b.x; }

template<class T>
double arg(const point<T> &a){
	double t=atan2(a.y,a.x);
	return t<0?t+2*PI:t;
}

template<class T>
struct line{
	point<T> a,b;
	operator line<double>()const{ return (line<double>){a,b}; }
};

enum {CCW=1,CW=-1,ON=0};
int ccw(const point<double> &a,const point<double> &b,const point<double> &c){
	double rdir=cross(b-a,c-a);
	if(rdir> EPS) return CCW;
	if(rdir<-EPS) return CW;
	return ON;
}

template<class T>
double dist(const point<T> &a,const point<T> &b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

template<class T>
bool cover(const point<T> &a,const point<T> &b,const point<T> &c,const point<T> &p){
	int d1=ccw(p,a,b);
	int d2=ccw(p,b,c);
	int d3=ccw(p,c,a);
	return !(d1==CCW && d2== CW || d1==CCW && d3== CW || d2==CCW && d3== CW
		  || d1== CW && d2==CCW || d1== CW && d3==CCW || d2== CW && d3==CCW);
}

point<double> get_intersect(const line<double> &L1,const line<double> &L2){
	double a1=cross(L1.b-L1.a,L2.b-L2.a);
	double a2=cross(L1.b-L1.a,L1.b-L2.a);
	if(abs(a1)<EPS) return L1.a;
	return L2.a+a2/a1*(L2.b-L2.a);
}

int n;
point<double> p[9]; // ??, ????????? p[n] ???????d?

bool vis[9];
double dfs(point<double> D,point<double> O,double r){ // ?????????, ?????????, ??????????
	if(D==p[n]) return 0;

	if(r+EPS<dist(O,p[n])) return INF;
// printf("D = (%.2f, %.2f)\n",D.x,D.y);
// printf("O = (%.2f, %.2f)\n",O.x,O.y);
// printf("r = %.2f\n",r);
	double res=INF;
	rep(i,n+1) if(!vis[i]) {
		// D ?????? P ???????????????????????????
		point<double> P=p[i];
		double t0=arg(D-O);

		if(ccw(O,D,P)!=ON){ // O, D, P ???????????????????????????
			int j0=-1; // ???????????????????????????????????
			rep(j,n) if(p[j]!=O && p[j]!=P && p[j]!=D) {
				if(cover(O,D,P,p[j])){ // ?????? ODP ???????? j ?????????????
					if(j0==-1) j0=j;
					else{
						double t1=arg(p[j0]-O)-t0; t1=min(abs(t1),abs(2*PI-t1));
						double t2=arg(p[j ]-O)-t0; t2=min(abs(t2),abs(2*PI-t2));
						if(t2+EPS<t1 || abs(t1-t2)<EPS && dist(p[j0],O)<dist(p[j],O)){
							j0=j;
						}
					}
				}
			}
			if(j0==-1){ // ?????????????????????????
				double d=dist(O,P);
				if(d<r+EPS){
					vis[i]=true;
					res=min(res,dist(D,P)+dfs(P,O,r));
					vis[i]=false;
				}
			}
			else{ // ?? j0 ????????????
				point<double> Q=get_intersect((line<double>){D,P},(line<double>){O,p[j0]});
				double d=dist(O,Q);
				if(d<r+EPS){
					res=min(res,dist(D,Q)+dfs(Q,p[j0],r-dist(O,p[j0])));
				}
			}
		}
		else{ // O, D, P ???????????????????????????
		}
	}

	return res;
}

int main(){
	for(;scanf("%d",&n),n;){
		point<double> D; // dog
		scanf("%lf%lf%lf%lf",&D.x,&D.y,&p[n].x,&p[n].y);
		rep(i,n) scanf("%lf%lf",&p[i].x,&p[i].y);

		point<double> O={0,0};
		double ans=dfs(D,O,dist(D,O));
		printf("%.9f\n",ans<INF/2?ans:-1);
	}

	return 0;
}
