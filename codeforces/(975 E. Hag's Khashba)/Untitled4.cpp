#include<bits/stdc++.h>
using namespace std;
typedef double ld;
const int N=20005;
int n,q,p1,p2;
inline ld sqr(ld x){return x*x;}
struct point{
	ld x,y;
	ld len(){return sqrtl(sqr(x)+sqr(y));}
	void read(){scanf("%lf %lf",&x,&y);}
	void print(){printf("%.8lf %.8lf\n",x,y);}
}a[N],cen,ang;
typedef point vec;
point operator+(point a,vec b){return (point){a.x+b.x,a.y+b.y};}
point operator-(point a,vec b){return (point){a.x-b.x,a.y-b.y};}
point operator*(vec a,vec b){return (vec){a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x};}
point operator*(vec a,ld k){return (vec){a.x*k,a.y*k};}
point operator/(vec a,ld k){return (vec){a.x/k,a.y/k};}
ld operator^(vec a,vec b){return a.x*b.y-a.y*b.x;}
vec unit(vec x){return x/x.len();}
point getp(int x){return a[x]*ang+cen;}
vec f(vec x){return (vec){x.x,-x.y};}
point getcen(point *a,int n){
	ld area=0,t;point cen={0,0};
	for (int i=3;i<=n;i++){
		t=((a[i-1]-a[1])^(a[i]-a[1]));
		cen=cen+(a[1]+a[i-1]+a[i])*t;
		area+=t;
	}
	return cen/3/area;
}
int main(){
//    freopen("in.txt", "r", stdin);
	scanf("%d %d",&n,&q);
	for (int i=1;i<=n;i++) a[i].read();
	cen=getcen(a,n);
	for (int i=1;i<=n;i++) a[i]=a[i]-cen;
//    cout<<cen.x<<' '<<cen.y<<endl;
//    exit(0);
	p1=1;p2=2;ang=(point){1,0};
	for (int i=1;i<=q;i++){
		int typ,x,y;
		scanf("%d",&typ);
		if (typ==1){
			scanf("%d %d",&x,&y);
			if (x==p1) swap(p1,p2);p2=y;
			vec cur=getp(p1);
			cen=cur-(point){0,a[p1].len()};
			ang=unit(f(a[p1]))*(vec){0,1};
		}
		else{
			scanf("%d",&x);
			(getp(x)).print();
		}
	}
	return 0;
}