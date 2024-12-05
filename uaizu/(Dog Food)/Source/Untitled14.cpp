#include<bits/stdc++.h>
#define inf 1<<29
#define linf 1e16
#define eps (1e-8)
#define mod 1000000007
#define pi acos(-1)
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define all(a) (a).begin(),(a).end()
#define pd(a) printf("%.10f\n",(double)(a))
#define FOR(i,a,b) for(int i=(a);i<(b);i++)
#define RFOR(i,a,b) for(int i=(a)-1;(b)<=i;i--)
#define equals(a,b) (fabs((a)-(b))<eps)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<int,double> pid;
typedef pair<double,int> pdi;
typedef vector<int> vi;
typedef vector<pii> vpi;
const int dx[8]={1,0,-1,0,1,1,-1,-1};
const int dy[8]={0,1,0,-1,1,-1,1,-1};

class Point{
public:
  double x,y;
  Point(double x=0,double y=0):x(x),y(y){}

  Point operator+(Point p){ return Point(x+p.x,y+p.y);}
  Point operator-(Point p){ return Point(x-p.x,y-p.y);}
  Point operator*(double k){ return Point(x*k,y*k);}
  Point operator/(double k){ return Point(x/k,y/k);}
  bool operator<(Point p)const{ return (x!=p.x ? x<p.x : y<p.y);}
  bool operator==(Point p)const{ return fabs(x-p.x)<eps && fabs(y-p.y)<eps;}

  double abs(){ return sqrt(norm());}
  double norm(){ return (x*x+y*y);}
};
typedef Point Vector;
typedef vector<Point> Polygon;

class Segment{
public:
  Point p1,p2;
  Segment(Point p1=Point(),Point p2=Point()):p1(p1),p2(p2){}
};
typedef Segment Line;

double norm(Vector a){ return (a.x*a.x+a.y*a.y);}
double abs(Vector a){ return sqrt(norm(a));}
double dot(Vector a,Vector b){ return (a.x*b.x+a.y*b.y);}
double cross(Vector a,Vector b){ return (a.x*b.y-a.y*b.x);}

int ccw(Point p0,Point p1,Point p2){
  Vector a=p1-p0;
  Vector b=p2-p0;
  if(cross(a,b)>eps)return 1;
  if(cross(a,b)<-eps)return -1;
  if(dot(a,b)<-eps)return 2;
  if(a.norm()<b.norm())return -2;
  return 0;
}

int contains(Polygon g,Point p){
  int n=g.size();
  bool x=false;
  for(int i=0;i<n;i++){
    Vector a=g[i]-p,b=g[(i+1)%n]-p;
    if(abs(cross(a,b))<eps && dot(a,b)<eps)return 1;
    if(a.y>b.y)swap(a,b);
    if(a.y<eps && eps<b.y && cross(a,b)>eps)x=!x;
  }
  if(x)return 2;
  return 0;
}

Polygon convex_hull(Polygon s){
  Polygon g;
  int n=s.size();
  if(n<3)return s;

  sort(s.begin(),s.end());

  for(int i=0;i<n;i++){
    for(int n=g.size();n>=2&&ccw(g[n-2],g[n-1],s[i])==1;n--){
      g.pop_back();
    }
    g.push_back(s[i]);
  }
  for(int i=n-2;i>=0;i--){
    for(int n=g.size();n>=2&&ccw(g[n-2],g[n-1],s[i])==1;n--){
      g.pop_back();
    }
    g.push_back(s[i]);
  }
  reverse(g.begin(),g.end());
  g.pop_back();
  return g;
}

double getCircumference(Polygon p){
  int n=p.size();
  double res=0;
  FOR(i,0,n)res+=abs(p[i]-p[(i+1)%n]);
  return res;
}

int n;
Point s,t;
vector<Point> vp;
bool used[10]={};

bool check(Point p,Point o,Point d,double dis){
  Polygon tr,cp;
  tr.pb(o);
  tr.pb(p);
  tr.pb(d);
  cp.pb(d);
  cp.pb(o);
  FOR(i,0,n){
    if(p==vp[i])continue;
    if(d==vp[i])continue;
    if(contains(tr,vp[i]))cp.pb(vp[i]);
  }
  cp = convex_hull(cp);
  if(getCircumference(cp)+dis-abs(d-o)-abs(s)<-eps)return true;
  return false;
}

pair<Point,double> getm(Point p,Point o,Point d){
  Polygon tr,cp;
  tr.pb(o);
  tr.pb(p);
  tr.pb(d);
  cp.pb(d);
  cp.pb(o);
  FOR(i,0,n){
    if(p==vp[i])continue;
    if(d==vp[i])continue;
    if(contains(tr,vp[i]))cp.pb(vp[i]);
  }
  cp = convex_hull(cp);
  Point res;
  FOR(i,0,cp.size())
    if(cp[i]==d && cp[(i+1)%cp.size()]==o)
      res = cp[(i-1+cp.size())%cp.size()];
  reverse(all(cp));
  FOR(i,0,cp.size())
    if(cp[i]==d && cp[(i+1)%cp.size()]==o)
      res = cp[(i-1+cp.size())%cp.size()];
  return mp(res,getCircumference(cp)-abs(d-o)-abs(res-d));
}

double rec(Point p,Point o,double dis,double sum){
  double res = inf;
  if(check(p,o,t,dis))return sum+abs(p-t);
  FOR(i,0,n){
    if(used[i])continue;
    used[i]=true;
    if(check(p,o,vp[i],dis)){
      pair<Point,double> no = getm(p,o,vp[i]);
      res=min(res,rec(vp[i],no.f,no.s+dis,sum+abs(vp[i]-p)));
    }
    used[i]=false;
  }
  return res;
}

double solve(){
  if(abs(s)<abs(t))return -1;
  double res=abs(s)+abs(t);
  res = min(res,rec(s,Point(0,0),0,0));
  return res;
}

int main()
{
  while(cin>>n && n){
    cin>>s.x>>s.y>>t.x>>t.y;
    vp.clear();
    FOR(i,0,n){
      int x,y;
      cin>>x>>y;
      vp.pb(Point(x,y));
    }
    pd(solve());
  }
  return 0;
}
