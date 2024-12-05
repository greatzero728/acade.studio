#include<bits/stdc++.h>
typedef long long int ll;
typedef unsigned long long int ull;
#define BIG_NUM 2000000000
#define HUGE_NUM 1000000000000000000
#define MOD 1000000007
#define EPS 0.000000001
using namespace std;


#define SIZE 10

int POW[9];

struct Point{
	Point(double arg_x,double arg_y){
		x = arg_x;
		y = arg_y;
	}

	Point(){
		x = y = 0.0;
	}

	Point operator + (Point p){ return Point(x+p.x,y+p.y); }
	Point operator - (Point p){ return Point(x-p.x,y-p.y);}
	Point operator * (double a){ return Point(a*x,a*y); }
	Point operator / (double a){ return Point(x/a,y/a); }

	double abs(){ return sqrt(norm()); }
	double norm(){ return x*x + y*y; }

	bool operator<(const Point &p) const{
		return x != p.x? x < p.x: y < p.y;
	}

	bool operator == (const Point &p) const{
		return fabs(x-p.x) < EPS && fabs(y-p.y) < EPS;
	}

   	/*
	void debug(){

		printf("(%.3lf,%.3lf)\n",x,y);
	}*/

	double x,y;
};

typedef Point Vector;
typedef vector<Point> Polygon;

double calc_dist(Point A,Point B){

	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}


int N;
double min_dist[SIZE][SIZE];
Point point[SIZE];

double norm(Vector a){
	return a.x*a.x+a.y*a.y;
}

double abs(Vector a){
	return sqrt(norm(a));
}

double cross(Vector a,Vector b){
    return a.x*b.y-a.y*b.x;
}

double dot(Vector a,Vector b){
    return a.x*b.x + a.y*b.y;
}

/*
 * IN 2
 * ON 1
 * OUT 0
 *
 */
int contains(Polygon g,Point p){
	int n = g.size();
	bool x = false;
	for(int i = 0; i < n; i++){
		Point a = g[i]-p,b = g[(i+1)%n]-p;
		if(abs(cross(a,b)) < EPS && dot(a,b) < EPS)return 1;
		if(a.y > b.y)swap(a,b);
		if(a.y < EPS && EPS < b.y && cross(a,b) > EPS) x = !x;
	}
	return (x ? 2:0);
}

static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE = -1;
static const int ONLINE_BACK = 2;
static const int ONLINE_FRONT = -2;
static const int ON_SEGMENT = 0;

int ccw(Point p0,Point p1,Point p2){

	Vector a = p1 - p0;
	Vector b = p2 - p0;

	if(cross(a,b) > EPS)return COUNTER_CLOCKWISE;
	if(cross(a,b) < -EPS)return CLOCKWISE;
	if(dot(a,b) < -EPS)return ONLINE_BACK;
	if(a.norm() < b.norm())return ONLINE_FRONT;

	return ON_SEGMENT;
}

Polygon ConvexHull(Polygon V){

	sort(V.begin(),V.end());

	vector<Point> UP,DOWN;

	UP.push_back(V[0]);
	DOWN.push_back(V[0]);

	for(int i = 1; i < V.size(); i++){

		while(UP.size() > 1 && ccw(UP[UP.size()-2],UP[UP.size()-1],V[i]) == COUNTER_CLOCKWISE){

			UP.pop_back();
		}

		while(DOWN.size() > 1 && ccw(DOWN[DOWN.size()-2],DOWN[DOWN.size()-1],V[i]) ==  CLOCKWISE){

			DOWN.pop_back();
		}

		UP.push_back(V[i]);
		DOWN.push_back(V[i]);
	}

	Polygon ret;

	for(int i = 0; i < UP.size(); i++){

		ret.push_back(UP[i]);
	}

	for(int i = DOWN.size()-1; i >= 0; i--){

		ret.push_back(DOWN[i]);
	}

	return ret;
}



void func(){

	int start = 0,goal = N+1;

	scanf("%lf %lf",&point[0].x,&point[0].y);
	scanf("%lf %lf",&point[N+1].x,&point[N+1].y);

	for(int i = 1; i <= N; i++){

		scanf("%lf %lf",&point[i].x,&point[i].y);
	}

	N += 1;

	Point house = Point(0,0);

	double len_rope = calc_dist(point[start],house);

	if(len_rope+EPS <  calc_dist(point[goal],house)){

		printf("-1\n");
		return;
	}

	double ans = BIG_NUM;

	Polygon P;
	P.push_back(house);
	P.push_back(point[start]);
	P.push_back(point[goal]);

	if(ccw(P[0],P[1],P[2]) == CLOCKWISE){

		swap(P[1],P[2]);
	}

	vector<int> OBST;

	for(int i = 1; i < N; i++){

		if(contains(P,point[i]) != 0){
			OBST.push_back(i);
		}
	}
	if(OBST.size() == 0){

		printf("%.10lf\n",calc_dist(point[start],point[goal]));
		return;
	}

	Polygon ROPE,MOVE;
	double tmp_len,tmp_dist;

	for(int state = 0; state < POW[OBST.size()]; state++){

		ROPE.clear();
		MOVE.clear();

		for(int loop = 0; loop < OBST.size(); loop++){
			if(state & POW[loop]){

				ROPE.push_back(point[OBST[loop]]);
			}else{

				MOVE.push_back(point[OBST[loop]]);
			}
		}

		ROPE.push_back(house);
		ROPE.push_back(point[goal]);

		MOVE.push_back(point[start]);
		MOVE.push_back(point[goal]);

		Polygon poly1  = ConvexHull(ROPE);

		tmp_len = 0;
		for(int i = 0; i < poly1.size(); i++){

			tmp_len += calc_dist(poly1[i],poly1[(i+1)%poly1.size()]);
		}
		tmp_len -= calc_dist(house,point[goal]);

		if(tmp_len > len_rope+EPS)continue;

		Polygon poly2 = ConvexHull(MOVE);

		tmp_dist = 0;

		for(int i = 0; i < poly2.size(); i++){

			tmp_dist += calc_dist(poly2[i],poly2[(i+1)%poly2.size()]);
		}
		tmp_dist -= calc_dist(point[start],point[goal]);

		ans = min(ans,tmp_dist);
	}

	if(fabs(ans-BIG_NUM) < EPS){

		printf("-1\n");
	}else{

		printf("%.10lf\n",ans);
	}
}

int main(){

	POW[0] = 1;
	for(int i = 1; i <= 8; i++){

		POW[i] = POW[i-1]*2;
	}

	while(true){

		scanf("%d",&N);
		if(N == 0)break;

		func();
	}

	return 0;
}
