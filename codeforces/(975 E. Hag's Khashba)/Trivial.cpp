#include<bits/stdc++.h>



#define x first

#define y second

#define eps 1e-7

#define pb push_back

#define inf 0x3f3f3f3f

#define mod 1000000007

#define sq(x) ((x)*(x))

#define cb(x) ((x)*(x)*(x))

#define bit(x, y) (((x)>>(y))&1)

#define bctz(x) (__builtin_ctz(x))

#define bclz(x) (__builtin_clz(x))

#define bclzl(x) (__builtin_clzl(x))

#define bctzl(x) (__builtin_ctzl(x))

#define bpt(x) (__builtin_popcount(x))

#define bptl(x) (__builtin_popcountll(x))

#define pi 3.1415926535897932384626433832795

#define PQ priority_queue<pii, vector<pii>, greater<pii> >



using namespace std;



typedef double DO;

typedef long long INT;

typedef vector<int> VI;

typedef pair<int, int> pii;

typedef pair<pii, int> pi3;



template<typename T, typename U> inline void smin(T &a, U b) {if(a>b) a=b;}

template<typename T, typename U> inline void smax(T &a, U b) {if(a<b) a=b;}



template <class T> inline void gn(T &x) {char c, sg=0; while(c=getchar(), (c>'9' || c<'0') && c!='-'); for((c=='-' ? sg=1, c=getchar() : 0), x=0; c>='0' && c<='9'; c=getchar()) x=(x<<1)+(x<<3)+c-'0'; if(sg) x=-x;}

template <class T1, class T2> inline void gn(T1 &x1, T2 &x2) {gn(x1), gn(x2);}

template <class T1, class T2, class T3> inline void gn(T1 &x1, T2 &x2, T3 &x3) {gn(x1, x2), gn(x3);}

template <class T1, class T2, class T3, class T4> inline void gn(T1 &x1, T2 &x2, T3 &x3, T4 &x4) {gn(x1, x2), gn(x3, x4);}



template <class T> inline void print(T x) {if(x<0) {putchar('-'); return print(-x);} if(x<10) {putchar('0'+x); return ;} print(x/10); putchar(x%10+'0');}

template <class T> inline void println(T x) {print(x); putchar('\n');}

template <class T> inline void printsp(T x) {print(x); putchar(' ');}

template <class T1, class T2> inline void print(T1 x1, T2 x2) {printsp(x1), println(x2);}

template <class T1, class T2, class T3> inline void print(T1 x1, T2 x2, T3 x3) {printsp(x1), printsp(x2), println(x3);}

template <class T1, class T2, class T3, class T4> inline void print(T1 x1, T2 x2, T3 x3, T4 x4) {printsp(x1), printsp(x2), printsp(x3), println(x4);}



int power(int a, int b, int m, int ans=1) {

	for(; b; b>>=1, a=1LL*a*a%m) if(b&1) ans=1LL*ans*a%m;

	return ans;

}



DO coss, sinn;



//2-dimension point struct (double)

struct point {

	DO x, y;

	point (DO x=0, DO y=0) : x(x), y(y) {}

	point operator - (point a) {return point(x-a.x, y-a.y);}

	point operator + (point a) {return point(x+a.x, y+a.y);}

	point operator * (DO a) {return point(x*a, y*a);}

	point operator / (DO a) {return point(x/a, y/a);}

	point operator & (point a) {return point(x*a.x-y*a.y, x*a.y+y*a.x);}

	point rotate() {return *this&point(coss, sinn);}

	DO    operator ^ (point a) {return x*a.y-y*a.x;}

	DO    operator * (point a) {return x*a.x+y*a.y;}

	point norm() {DO s=nor(); if (s<eps) return *this; return point(x/s, y/s);}

	point conj() {return point(-y, x);}

	DO nor() {return sqrt(*this**this);}

	DO al() {return atan2(y, x);}

	bool operator < (const point &a) const {

		if (fabs(x-a.x)>eps) return x<a.x;

		return y<a.y-eps;

	}

	bool operator > (const point &a) const {

		if (fabs(x-a.x)>eps) return x>a.x;

		return y>a.y+eps;

	}

	bool operator == (const point &a) const {

		if (fabs(x-a.x)>eps) return 0;

		return fabs(y-a.y)<eps;

	}

	bool operator != (const point &a) const {

		if(*this==a) return false;

		return true;

	}

	void input() {scanf("%lf %lf", &x, &y);}

	void print() {printf("%lf %lf\n", x, y);}

};



#define NN 10010



point p[NN], center, dir[NN];

int n, q;

DO d[NN];



void init() {

	DO area=0;

	for(int i=2; i<n; i++) {

		DO tmp=fabs(p[i]-p[1]^p[i+1]-p[1])/2;

		point pp=(p[1]+p[i]+p[i+1])/3;

		center=center+pp*tmp;

		area+=tmp;

	}

	center=center/area;

	for(int i=1; i<=n; i++) {

		dir[i]=p[i]-center;

		d[i]=dir[i].nor();

	}

}



point update(int u, int v) {

	coss=dir[u]*dir[v]/d[u]/d[v];

	sinn=dir[u]^dir[v]/d[u]/d[v];

	

	return center+(p[u]-center).rotate().norm()*d[v];

}



int main() {

#ifndef	ONLINE_JUDGE

	freopen("in.txt", "r", stdin);

//	freopen("out.out", "w", stdout);

#endif



	gn(n, q);

	for(int i=1; i<=n; i++) p[i].input();

	

	init();

	int ia=1, ib=2;

	while(q--) {

		int t, f, u;

		gn(t);

		if(t==1) {

			gn(f, u);

			if(ia==f) swap(ia, ib);

			

			center=point(p[ia].x, p[ia].y-d[ia]);

			p[u]=update(ia, u);

			ib=u;

		}

		else {

			gn(u);

			p[u]=update(ia, u);

			p[u].print();

		}

	}

}
  