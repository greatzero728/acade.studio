#include <bits/stdc++.h>
#define   maxN  100001

using namespace std;
struct Point{
   long long   x,y;
   Point(long long a, long long b){x=a; y=b;}
   Point(){};
};
struct Segment{
  Point a, b;
  Segment(){};
  Segment(Point aa, Point bb){a=aa; b=bb;}
};

Segment S[maxN];
pair<int,bool> AB[2*maxN];
Point Rmost[maxN];
vector<Segment> Sol;
int n;

int Turn(Point A, Point B, Point C){
   long long Kereszt=(B.x-A.x)*(C.y-A.y)-(C.x-A.x)*(B.y-A.y);
   if (Kereszt <0)
      return -1;
   else if (Kereszt >0)
      return 1;
   else
      return  0;
}
struct SegOrd{
  bool operator() (const int& u, const int& v) const{
    int tua=Turn(S[u].a,S[u].b,S[v].a);
    int tub=Turn(S[u].a,S[u].b,S[v].b);
    int tva=Turn(S[v].a,S[v].b,S[u].a);
    int tvb=Turn(S[v].a,S[v].b,S[u].b);
    return  tua>0 && tub>0 || tva<0 && tvb<0 ||
            tua==0 && tub==0&& tva==0 && tvb==0 && S[u].a.y<S[v].a.y;
  }
};

set<int, SegOrd> Sline;

bool ABord(pair<int,bool> a, pair<int,bool> b){
  Point ap,bp;
  if(a.second) ap=S[a.first].a; else ap=S[a.first].b;
  if(b.second) bp=S[b.first].a; else bp=S[b.first].b;
  if(ap.x<bp.x) return true;
  if(ap.x>bp.x) return false;
  return (ap.y<bp.y);
}

void ReadIn(){
  int x1,y1,x2,y2;
  cin>>n;
  for(int i=0;i<n;i++){
    cin>>x1>>y1>>x2>>y2;
    if(x1<x2 || x1==x2 && y1<y2)
      S[i]={{x1,y1},{x2,y2}};
    else
      S[i]={{x2,y2},{x1,y1}};
  }
}

int main(){
  ReadIn();
  for(int i=0;i<n;i++){
    AB[i]={i,true};
    AB[i+n]={i,false};
  }
  sort(AB, AB+2*n, ABord);
  long long maxxy=10000000;
  Segment sentinel={{-maxxy,-maxxy},{maxxy, -maxxy}};
  S[n]=sentinel;   Sline.insert(n);
  int s0=AB[0].first;
  Sline.insert(s0);
  if(S[s0].a.x!=S[s0].b.x){
    Rmost[n]=S[s0].a;
    Rmost[s0]=S[s0].a;
  }else{
    Rmost[s0]=S[s0].b;
    Rmost[n]=S[s0].b;
  }
//
  set<int, SegOrd>::iterator p,pp;
  for(int i=1;i<2*n;i++){
    if(AB[i].second){//left endpoint
      p=Sline.insert(AB[i].first).first;
      pp=p; pp--;
      Sol.push_back({S[*p].a,Rmost[*pp]});
      if(S[*p].a.x!=S[*p].b.x)
        Rmost[*p]=S[*p].a;
      else
        Rmost[*p]=S[*p].b;
      Rmost[*pp]=S[*p].a;
    }else{//right endpoint
      p=Sline.find(AB[i].first);
      pp=p; pp--;
      Rmost[*pp]=S[*p].b;
      Sline.erase(p);
    }
  }
//
  for(auto ab:Sol)
    cout<<ab.a.x<<" "<<ab.a.y<<" "<<ab.b.x<<" "<<ab.b.y<<"\n";
  return 0;
}
