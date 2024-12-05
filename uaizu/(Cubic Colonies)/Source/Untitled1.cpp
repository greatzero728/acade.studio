#include<bits/stdc++.h>
typedef long long int ll;
typedef unsigned long long int ull;
#define BIG_NUM 2000000000
#define HUGE_NUM 1000000000000000000
#define MOD 1000000007
#define EPS 0.000000001
using namespace std;


#define SIZE 10005

enum DIR{
	UP,
	East,
	North,
	West,
	South,
	Down,
};


struct LOC{
	void set(int arg_X,int arg_Y,int arg_Z){
		X = arg_X;
		Y = arg_Y;
		Z = arg_Z;
	}
	/*void debug(){

		printf("X:%d Y:%d Z:%d\n",X,Y,Z);
	}*/
	int X,Y,Z;
};


struct Point3D{
	Point3D(double arg_x,double arg_y,double arg_z){
		x = arg_x;
		y = arg_y;
		z = arg_z;
		X = Y = Z = 0;
	}

	Point3D(){
		x = y = z = 0.0;
		X = Y = Z = 0;
	}

	Point3D operator + (Point3D p){ return Point3D(x+p.x,y+p.y,z+p.z); }
	Point3D operator - (Point3D p){ return Point3D(x-p.x,y-p.y,z-p.z);}
	Point3D operator * (double a){ return Point3D(a*x,a*y,a*z); }
	Point3D operator / (double a){ return Point3D(x/a,y/a,z/a); }

	double abs(){ return sqrt(norm()); }
	double norm(){ return x*x + y*y + z*z; }

	bool operator<(const Point3D &p) const{
		if(fabs(x-p.x) > EPS){

			return x < p.x;
		}else if(fabs(y-p.y) > EPS){

			return y < p.y;
		}else{

			return z < p.z;
		}
	}

	void set(int arg_X,int arg_Y,int arg_Z){
		X = arg_X;
		Y = arg_Y;
		Z = arg_Z;
	}

	void copy(){
		x = X;
		y = Y;
		z = Z;
	}

	bool operator == (const Point3D &p) const{
		return fabs(x-p.x) < EPS && fabs(y-p.y) < EPS && fabs(z-p.z) < EPS;
	}
	/*void debug(){

		printf("(%.3lf,%.3lf,%.3lf)\n",x,y,z);
	}*/
	int X,Y,Z;
	double x,y,z;
};

typedef Point3D Vector3D;

struct Line{
	Line(){

	}
	Line(Point3D a,Point3D b){
		p[0] = a;
		p[1] = b;
	}
	/*void outPut(){

		printf("(%.3lf,%.3lf)-(%.3lf,%.3lf)\n",p[0].x,p[0].y,p[1].x,p[1].y);
	}*/
	Point3D p[2];
};

struct Data{
	Data(){

		X = Y = Z = 0;
		x = y = z = 0;
	}
	Data(double arg_x,double arg_y,double arg_z){
		x = arg_x;
		y = arg_y;
		z = arg_z;
		X = Y = Z = 0;
	}

	void set(int arg_X,int arg_Y,int arg_Z){
		X = arg_X;
		Y = arg_Y;
		Z = arg_Z;
	}
	void copy(){
		x = X;
		y = Y;
		z = Z;
	}
	void debug(){

		printf("%d %d %d\n",X,Y,Z);
	}
	int X,Y,Z;
	double x,y,z;
};

struct Seg{
	void set(int arg_A,int arg_B){
		A = arg_A;
		B = arg_B;
	}
	int A,B;
};

struct Edge{
	Edge(int arg_to,double arg_dist){
		to = arg_to;
		dist = arg_dist;
	}
	int to;
	double dist;
};

struct Info{
	Info(){
		index = 0;
	}
	Info(Point3D arg_p,int arg_index){
		p = arg_p;
		index = arg_index;
	}
	bool operator<(const struct Info &arg)const{

		return p < arg.p;
	}
	bool operator==(const struct Info &arg) const{

		return p == arg.p;
	}
	Point3D p;
	int index;
};

struct State{
	State(int arg_node_id,double arg_sum_dist){
		node_id = arg_node_id;
		sum_dist = arg_sum_dist;
	}
	bool operator<(const struct State  &arg) const{

		return sum_dist > arg.sum_dist; //??????(PQ)
	}
	int node_id;
	double sum_dist;
};

int num_loc,num_data,num_POINT,num_seg;
int S,T;
int ADJ[27][6];
int loc_X[6] = {0,1,0,-1,0,0},loc_Y[6] = {-1,0,0,0,0,1},loc_Z[6] = {0,0,1,0,-1,0};
int D_X[8] = {0,1,0,1,0,1,0,1},D_Y[8] = {0,0,0,0,1,1,1,1},D_Z[8] = {0,0,1,1,0,0,1,1};
int have_L[6][4] ={{0,1,2,3},{1,5,9,10},{2,6,10,11},{3,7,8,11},{0,4,8,9},{4,5,6,7}};
int L_array[12][2] = {{0,1},{1,3},{2,3},{0,2},{4,5},{5,7},{6,7},{4,6},{0,4},{1,5},{3,7},{2,6}};
int D[27][8];
int SEG[27][12];
int POS[9][3] = {{0,1,2},{9,10,11},{18,19,20},{3,4,5},{12,13,14},{21,22,23},{6,7,8},{15,16,17},{24,25,26}};
int four_line[27][6][4];
double min_dist[SIZE];
bool EXIST[27],check[144];
char input_str[9][4];
Point3D start,goal;
Data first_D[27][8];
Data data[64];
Seg first_seg[27][12];
Seg seg[144];
LOC loc[27]; //???????
vector<Edge> G[SIZE];
Point3D POINT[SIZE];
vector<Info> info;
vector<int> LINE[144];



double calc_dist(Point3D A,Point3D B){

	double a = A.x-B.x;
	double b = A.y-B.y;
	double c = A.z-B.z;

	return sqrt(a*a+b*b+c*c);
}

void func(){

	for(int i = 0; i < num_POINT; i++){

		G[i].clear();
	}
	for(int i = 0; i < num_seg; i++){

		check[i] = false;
	}

	for(int row = 0; row < 9; row++){
		scanf("%s",input_str[row]);
	}

	//???????????
	for(int row = 0; row < 9; row++){
		for(int col = 0; col < 3; col++){
			if(input_str[row][col] == '#'){

				EXIST[POS[row][col]] = true;

			}else{

				EXIST[POS[row][col]] = false;
			}
		}
	}

	S = -1;
	for(int i = 0; i < num_POINT; i++){

		if(start.X == POINT[i].X && start.Y == POINT[i].Y && start.Z == POINT[i].Z){

			S = i;
			break;
		}
	}
	T = -1;
	for(int i = 0; i < num_POINT; i++){

		if(goal.X == POINT[i].X && goal.Y == POINT[i].Y && goal.Z == POINT[i].Z){

			T = i;
			break;
		}
	}


	//????????&?????
	for(int i = 0; i <= 26; i++){
		if(!EXIST[i])continue;
		for(int k = 0; k < 6; k++){
			if(ADJ[i][k] == -1 || !EXIST[ADJ[i][k]]){
				for(int a = 0; a < 4; a++){
					int from = four_line[i][k][a]; //??index

					//?????????
					if(!check[from]){
						check[from] = true;
						for(int b = 1; b < LINE[from].size(); b++){

							double tmp_dist = calc_dist(POINT[LINE[from][b-1]],POINT[LINE[from][b]]);

							G[LINE[from][b-1]].push_back(Edge(LINE[from][b],tmp_dist));
							G[LINE[from][b]].push_back(Edge(LINE[from][b-1],tmp_dist));
						}
					}
					//??????????
					for(int b = a+1; b < 4; b++){
						int to = four_line[i][k][b];
						for(int c = 0; c < LINE[from].size(); c++){
							for(int d = 0; d < LINE[to].size(); d++){

								int A = LINE[from][c];
								int B = LINE[to][d];
								if(A == B)continue;

								double tmp_dist = calc_dist(POINT[A],POINT[B]);

								G[A].push_back(Edge(B,tmp_dist));
								G[B].push_back(Edge(A,tmp_dist));
							}
						}
					}
				}
			}
		}
	}

	for(int i = 0; i < num_POINT; i++){

		min_dist[i] = BIG_NUM;
	}

	priority_queue<State> Q;
	min_dist[S] = 0;

	Q.push(State(S,0));

	int next_node;
	double next_dist;

	while(!Q.empty()){

		if(Q.top().sum_dist > min_dist[Q.top().node_id]+EPS){

			Q.pop();
		}else if(Q.top().node_id == T){

			printf("%.10lf\n",Q.top().sum_dist);
			return;

		}else{

			for(int i = 0; i < G[Q.top().node_id].size(); i++){

				next_node = G[Q.top().node_id][i].to;
				next_dist = Q.top().sum_dist+G[Q.top().node_id][i].dist;

				if(min_dist[next_node] > next_dist+EPS){
					min_dist[next_node] = next_dist;
					Q.push(State(next_node,next_dist));
				}
			}
			Q.pop();
		}
	}
}

bool rangeCheck(int value){

	return value >= 0 && value <= 2;
}

void calc_ADJ(){

	num_loc = 0;

	for(int Y = 0; Y <= 2; Y++){
		for(int Z = 0; Z <= 2; Z++){
			for(int X = 0; X <= 2; X++){

				loc[num_loc].set(X,Y,Z);
				num_loc++;
			}
		}
	}

	for(int i = 0; i <= 26; i++){
		for(int k = 0; k < 6; k++){

			int adj_X = loc[i].X+loc_X[k];
			int adj_Y = loc[i].Y+loc_Y[k];
			int adj_Z = loc[i].Z+loc_Z[k];

			if(adj_X >= 0 && adj_X <= 2 && adj_Y >= 0 &&
					adj_Y <= 2 && adj_Z >= 0 && adj_Z <= 2){

				for(int a = 0; a <= 26; a++){
					if(adj_X == loc[a].X && adj_Y == loc[a].Y && adj_Z == loc[a].Z){
						ADJ[i][k] = a;
						break;
					}
				}

			}else{

				ADJ[i][k] = -1;
			}
		}
	}
}

void calc_PL(){

	//?????????8???
	for(int i = 0; i <= 26; i++){
		for(int k = 0; k <= 7; k++){
			int X = loc[i].X+D_X[k];
			int Y = loc[i].Y+D_Y[k];
			int Z = loc[i].Z+D_Z[k];

			first_D[i][k].set(X,Y,Z);
		}
	}

	//index?????
	num_data = 0;
	for(int i = 0; i <= 26; i++){
		for(int k = 0; k <= 7; k++){

			int X = first_D[i][k].X;
			int Y = first_D[i][k].Y;
			int Z = first_D[i][k].Z;

			bool FLG = false;
			for(int a = 0; a < num_data; a++){
				if(X == data[a].X && Y == data[a].Y && Z == data[a].Z){
					D[i][k] = a;
					FLG = true;
					break;
				}
			}

			if(!FLG){
				D[i][k] = num_data;
				data[num_data].set(X,Y,Z);
				num_data++;
			}
		}
	}

	for(int i = 0; i < num_data; i++){

		data[i].copy();
	}

	num_POINT = 0;
	for(int i = 0; i < num_data; i++){
		POINT[i].X = data[i].X;
		POINT[i].Y = data[i].Y;
		POINT[i].Z = data[i].Z;
		POINT[i].copy();
		num_POINT++;
	}

	//6??4??????
	num_seg = 0;
	int tmp_index;

	for(int i = 0; i <= 26; i++){
		for(int k = 0; k < 6; k++){ //?
			for(int p = 0; p < 4; p++){
				int from = D[i][L_array[have_L[k][p]][0]];
				int to = D[i][L_array[have_L[k][p]][1]];

				if(from > to){

					swap(from,to);
				}
				tmp_index = -1;
				for(int a = 0; a < num_seg; a++){
					if(seg[a].A == from && seg[a].B == to){

						tmp_index = a;
						break;
					}
				}
				if(tmp_index == -1){

					tmp_index = num_seg;
					seg[num_seg].A = from;
					seg[num_seg].B = to;
					num_seg++;
				}
				four_line[i][k][p] = tmp_index;
			}
		}
	}

	//???????
	for(int i = 0; i < num_seg; i++){
		info.clear();
		info.push_back(Info(POINT[seg[i].A],seg[i].A));
		info.push_back(Info(POINT[seg[i].B],seg[i].B));
		sort(info.begin(),info.end());
		Point3D p_L = info[0].p,p_R = info[1].p;
		for(int ALL = 2; ALL <= 9; ALL++){
			for(int left = 1; left <= ALL-1; left++){
				int right = ALL-left;
				Point3D tmp_p = (p_R*(double)(left)+p_L*(double)(right))/(double)ALL;

				int tmp_id = -1;
				for(int a = 0; a < num_POINT; a++){

					if(POINT[a] == tmp_p){

						tmp_id = a;
						break;
					}
				}
				if(tmp_id == -1){
					tmp_id = num_POINT;
					POINT[num_POINT] = tmp_p;
					POINT[num_POINT].X = -1;
					num_POINT++;
				}
				info.push_back(Info(tmp_p,tmp_id));
			}
		}
		sort(info.begin(),info.end());
		info.erase(unique(info.begin(),info.end()),info.end());

		for(int a = 0; a < info.size(); a++){

			LINE[i].push_back(info[a].index);
		}
	}
}


int main(){

	calc_ADJ();
	calc_PL();

	while(true){

		scanf("%d %d %d %d %d %d",&start.X,&start.Y,&start.Z,&goal.X,&goal.Y,&goal.Z);
		if(start.X == 0 && start.Y == 0 && start.Z == 0 && goal.X == 0 && goal.Y == 0 && goal.Z == 0)break;

		func();
	}

	return 0;
}
