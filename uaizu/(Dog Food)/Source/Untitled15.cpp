#include<cstdio>
#include<complex>
#include<cmath>
#include<vector>
#include<algorithm>

using namespace std;

typedef double Real;

typedef complex<Real> Point;
typedef complex<Real> Vector;
typedef pair<Point,Point> Segment;
typedef vector<Point> Polygon;
typedef pair<Point,Point> Line;

const Real eps=1e-9;
const Real PI=acos(-1.0);

template<class T> bool eq(T a,T b){
	return abs(a-b)<eps;
}
template<class T> int sgn(T a){
	if(eq(a,0.0)) return 0;
	if(a>0) return 1;
	return -1;
}

Real arg(Vector a){
	return atan2(a.imag(),a.real());
}

Real doP(Vector a,Vector b){
	return (conj(a)*b).real();
}

Real crP(Vector a,Vector b){
	return (conj(a)*b).imag();
}

Point iLL(Line l1,Line l2){
	Point a=l1.first,b=l1.second;
	Point c=l2.first,d=l2.second;
	Real num=crP(c-a,d-a);
	Real den=crP(b-a,d-c);
	return a+(b-a)*num/den;
}

Point start,goal;
Point pts[10];
int N;

struct State{
	Point center;
	Real radius;
	Point start,goal;
	State(){}
	bool isValid(){
		if(sgn(abs(goal-center)-radius)>0) return false;
		return true;
	}
	State getNext(){
		if(sgn(crP(goal-start,-start))==0){
			State res(*this);
			res.start=goal;
			return res;
		}
		Real curAng=-1;
		Real curDis=-1;
		Point nxtCenter=center;
		for(int i=0;i<N;i++){
			Point p=pts[i];
			int s1=sgn(crP(goal-start,p-start));
			int s2=sgn(crP(center-goal,p-goal));
			int s3=sgn(crP(start-center,p-center));
			if(s1*s3==0) continue;
			if(s2==0) s2=s1;
			if(s1!=s2||s1!=s3) continue;
			Real num=arg((p-center)/(start-center));
			Real den=arg((goal-center)/(start-center));
			Real ang=num/den;
			Real dis=abs(p-center);
			if(eq(curAng,-1.0)||sgn(curAng-ang)>0||(sgn(curAng-ang)==0&&sgn(curDis-dis)<0)){
				nxtCenter=p;
				curAng=ang;
				curDis=dis;
			}
		}
		if(eq(nxtCenter,center)){
			State res(*this);
			res.start=goal;
			return res;
		}
		Point nxtStart=iLL(Line(center,nxtCenter),Line(start,goal));
		State res;
		res.start=nxtStart;
		res.goal=goal;
		res.radius=radius-abs(nxtCenter-center);
		res.center=nxtCenter;
		return res;
	}
};

Point readP(){
	int x,y;
	scanf("%d%d",&x,&y);
	return Point(x,y);
}

void input(){
	scanf("%d",&N);
	if(N==0) exit(0);
	start=readP();
	goal=readP();
	for(int i=0;i<N;i++) pts[i]=readP();
	pts[N]=start;
	pts[N+1]=goal;
}

vector<vector<int> > ord;

vector<int> vec;
bool used[8];
void dfs(){
	vec.push_back(N+1);
	ord.push_back(vec);
	vec.pop_back();
	for(int i=0;i<N;i++){
		if(used[i]) continue;
		vec.push_back(i);
		used[i]=true;
		dfs();
		used[i]=false;
		vec.pop_back();
	}
}

int main(){
	while(true){
		input();
		vec.clear();
		vec.push_back(N);
		ord.clear();
		for(int i=0;i<N;i++) used[i]=false;
		dfs();
		Real ans=-1;
		for(int i=0;i<ord.size();i++){
			vector<int> ord=::ord[i];
			Real dis=0;
			State state;
			state.start=pts[ord[0]];
			state.radius=abs(start);
			state.center=Point(0,0);
			bool suc=true;
			for(int j=1;j<ord.size();j++){
				state.goal=pts[ord[j]];
				dis+=abs(pts[ord[j]]-pts[ord[j-1]]);
				while(true){
					if(state.isValid()==false){
						suc=false;
						break;
					}
					state=state.getNext();
					if(eq(state.start,state.goal)) break;
				}
			}
			if(suc){
				if(eq(ans,-1.0)||sgn(ans-dis)>0){
					ans=dis;
				}
			}
		}
		if(ans<0){
			printf("-1\n");
		}else{
			printf("%f\n",ans);
		}
	}
	return 0;
}
