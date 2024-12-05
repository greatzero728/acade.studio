#include <algorithm>
#include <queue>
#include <iostream>
#include <set>
#include <cstdio>
#include <complex>
#include <cmath>
#include <cfloat>

#define REP(i,n) for(int i=0; i<(int)(n); i++)

inline int getInt(){ int s; scanf("%d", &s); return s; }
inline double getDouble(){ double s; scanf("%lf", &s); return s; }
using namespace std;

typedef complex<double> P;

struct S{
  P p1;
  P p2;
  S(P p,P q) : p1(p), p2(q) {}
};

int ccw(P p0, P p1, P p2){
  P d1 = p1-p0;
  P d2 = p2-p0;
  double dx1 = d1.real(), dx2 = d2.real();
  double dy1 = d1.imag(), dy2 = d2.imag();

  if(dx1*dy2 > dy1*dx2) return  1;
  if(dx1*dy2 < dy1*dx2) return -1;
  if((dx1*dx2 < 0) || (dy1*dy2 < 0)) return -1;
  if((dx1*dx1+dy1*dy1) < (dx2*dx2+dy2*dy2)) return 1;
  return 0;
}

bool intersect(const S &s1, const S &s2){
  return ((ccw(s1.p1, s1.p2, s2.p1)
           *ccw(s1.p1, s1.p2, s2.p2)) <= 0)
    &&((ccw(s2.p1, s2.p2, s1.p1)
        *ccw(s2.p1, s2.p2, s1.p2)) <= 0);
}

#define PP(p, i, n) (p[((i)==-1 ? (n)-1 : (i))])

bool inside(P t, P *p, int N){
  int count = 0;
  S lt(t, P(DBL_MAX,t.imag() + 1e-3));

  for(int i=0; i<N; i++){
    S lp(p[i == 0 ? N - 1 : i - 1], p[i]);
    if(ccw(lt.p1, lt.p2, p[i == 0 ? N - 1 : i - 1]) != 0){
      if(intersect(lp,lt)) count++;
    }else{
      return false;
    }
  }
  // printf("%d ", count);
  return (count & 1) == 1;
}

struct cmpTheta{
  const P base;
  cmpTheta(P p) : base(p) {}

  bool operator () (const P &p1, const P &p2) const{
    P ang1 = (p1 - base) / abs(p1 - base);
    P ang2 = (p2 - base) / abs(p2 - base);
    return (ang1 / ang2).imag() < 0;
  }
};

int grahamscan(P *p, int N){
  int min, M, i;
  for(min=0, i=0; i<N; i++)
    if(p[i].imag() < p[min].imag())
      min=i;

  for(i=0; i<N; i++)
    if(p[i].imag() == p[min].imag())
      if(p[i].real() > p[min].real())
        min = i;

  swap(p[min], p[0]);

  sort(p+1, p+N, cmpTheta(p[0]));

  for(M=2, i=3; i<N; i++){
    while(ccw(PP(p,M,N),PP(p,M-1,N),PP(p,i,N)) >= 0) M--;
    M++; swap(p[i], p[M]);
  }

  return M + 1;
}

int main(){
  while(const int n = getInt()){
    P dog;
    P food;
    vector<P> p(n);

    dog.real() = getDouble();
    dog.imag() = getDouble();

    const double len = std::abs(dog);
    const double EPS = 1e-8;

    food.real() = getDouble();
    food.imag() = getDouble();

    REP(i,n){
      p[i].real() = getDouble();
      p[i].imag() = getDouble();
    }

    if(len + EPS < std::abs(food)){
      puts("-1");
      continue;
    }

    const double PI = acos(0) * 2.0;

    {
      double ang = arg(dog);
      P rot = P(cos(-ang), sin(-ang));

      dog *= rot; food *= rot;
      REP(i,n) p[i] *= rot;
    }

    if(arg(food) < 0){
      food.imag() *= -1;
      REP(i,n) p[i].imag() *= -1;
    }

    vector<pair<double, int> > memo(n);
    REP(i,n){
      memo[i].first  = arg(p[i]);
      memo[i].second = i;
    }

    sort(memo.begin(), memo.end());

    vector<P> ps;

    REP(i,n){
      if(arg(dog) < memo[i].first &&
         memo[i].first < arg(food)){
        ps.push_back(p[memo[i].second]);
      }
    }

    const int m = ps.size();
    double ans = std::abs(food) + std::abs(dog);
    /*{ printf("%d: %.2f %.2f\n", -1, dog.real(), dog.imag()); }
    REP(i,m){ printf("%d: %.2f %.2f\n", i, ps[i].real(), ps[i].imag()); }
    { printf("%d: %.2f %.2f\n", -2, food.real(), food.imag()); }*/

    REP(i,1 << m){
      vector<P> t;
      t.push_back(P(0,0));
      t.push_back(dog);
      REP(j,m) if(i & (1 << j))
        t.push_back(ps[j]);
      t.push_back(food);

      vector<P> in;
      in.push_back(P(0,0));

      REP(j,m) if((i & (1 << j)) == 0){
        if(inside(ps[j], &t[0], t.size()))
          in.push_back(ps[j]);
      }

      in.push_back(food);

      /*{
        puts("");
        printf("%d:\n", i);
        REP(j,in.size()) printf("%.2f %.2f ", in[j].real(), in[j].imag());
        puts("");
        }*/

      const int g = in.size() != 2 ? grahamscan(&in[0], in.size()) : 2;

      /*{
        printf("g: %d\n", g);
        REP(j,g) printf("%.2f %.2f ", in[j].real(), in[j].imag());
        puts("");
        }*/

      double tmp = 0.0;

      int s = 0;
      REP(j,g) if(abs(in[j] - P(0,0)) < EPS){
        s = j; break;
      }

      if(std::abs(in[(s + g - 1) % g] - food) > EPS){
        reverse(in.begin(), in.begin() + g);
      }

      REP(j,g) if(abs(in[j] - P(0,0)) < EPS){
        s = j; break;
      }

      REP(j,g - 1)
        tmp += std::abs(in[(s + j + 1) % g] - in[(s + j) % g]);


      double ret = 0.0;
      REP(j,t.size() - 2)
        ret += std::abs(t[j + 2] - t[j + 1]);

      // printf("tmp:%.2f ret:%.2f\n", tmp, ret);

      if(tmp < len)
        ans = min(ans, ret);
    }

    printf("%.8f\n", ans);
  }
  return 0;
}
